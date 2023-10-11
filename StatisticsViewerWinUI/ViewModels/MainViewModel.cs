using System;
using System.IO;
using System.Data;
using System.Text;

using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading.Tasks;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

using CommunityToolkit.Mvvm.Input;

using StatisticsViewerWinUI.Dialogs;

using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.ApplicationModel.DataTransfer;

using StatisticsViewerWinUI.Model;

using StatisticsLibraryWRC;
using CommunityToolkit.Mvvm.Messaging;
using CommunityToolkit.Mvvm.DependencyInjection;
using System.Windows.Input;
using Microsoft.UI.Xaml.Controls.Primitives;

namespace StatisticsViewerWinUI.ViewModels
{
    public class UpdateMessage
    {
        public void UpdateData() { }
    }

    public class MainViewModel : BindableBase
    {
        private bool m_darkMode;

        // Model entities
        private DataManager m_dataManager;
        private Statistics m_statisticsOps;

        // Model wrapper around a named data set
        private ObservableCollection<Model.DataSet> m_dataSetNames = new();
        
        // The collection of results from a specific statistical operation
        private ObservableCollection<ResultStatistic> m_results = new();

        // The collection of data
        private ObservableCollection<object> m_dataCollection;

        #region Menu Commands
        public RelayCommand FileExitCommand { get; set; }
        public RelayCommand FileOpenCommand { get; set; }

        public RelayCommand StatisticsDescriptiveCommand { get; set; }
        public RelayCommand StatisticsLinearRegressionCommand { get; set; }

        public RelayCommand TestsSummaryDataTTestCommand { get; set; }
        public RelayCommand TestsOneSampleTTestCommand { get; set; }
        public RelayCommand TestsTwoSampleTTestCommand { get; set; }

        public RelayCommand TestsSummaryDataFTestCommand { get; set; }
        public RelayCommand TestsTwoSampleFTestCommand { get; set; }

        public RelayCommand ThemeDarkCommand { get; set; }
        public RelayCommand ThemeLightCommand { get; set; }

        public RelayCommand HelpAboutCommand { get; set; }

        public RelayCommand ResultsCopyCommand { get; set; }
        #endregion

        #region Construction
        public MainViewModel()
        {
            DarkMode = App.Current.RequestedTheme == ApplicationTheme.Dark ? true : false;

            m_dataManager = Ioc.Default.GetService<DataManager>();
            m_statisticsOps = Ioc.Default.GetService<Statistics>();

            FileOpenCommand = new RelayCommand(FileOpen);
            FileExitCommand = new RelayCommand(FileExit);

            StatisticsDescriptiveCommand = new RelayCommand(StatisticsDescriptive, () => m_dataManager.CountDataSets > 0) ;
            StatisticsLinearRegressionCommand = new RelayCommand(StatisticsLinearRegression, () => m_dataManager.CountDataSets > 1);

            TestsSummaryDataTTestCommand = new RelayCommand(SummaryDataTTest);
            TestsOneSampleTTestCommand = new RelayCommand(OneSampleTTest, () => m_dataManager.CountDataSets > 0);
            TestsTwoSampleTTestCommand = new RelayCommand(TwoSampleTTest, () => m_dataManager.CountDataSets > 1);

            TestsSummaryDataFTestCommand = new RelayCommand(SummaryDataFTest);
            TestsTwoSampleFTestCommand = new RelayCommand(TwoSampleFTest, () => m_dataManager.CountDataSets > 1);

            ThemeDarkCommand = new RelayCommand(SetDarkTheme);
            ThemeLightCommand = new RelayCommand(SetLightTheme);

            HelpAboutCommand = new RelayCommand(HelpAbout);

            ResultsCopyCommand = new RelayCommand(ResultsCopy, () => Results.Count > 0);
        }
        #endregion

        #region Public Functions
        public IList<object> ListDataSets()
        {
            return m_dataManager.ListDataSets();
        }
        #endregion

        #region Bound Properties

        public bool DarkMode 
        {
            get
            {
                return m_darkMode;
            }
            set
            {
                SetProperty(ref m_darkMode, value);
            }
        }

        public ObservableCollection<object> Collection
        {
            get
            {
                return m_dataCollection;
            }
        }

        public ObservableCollection<ResultStatistic> Results
        {
            get
            {
                return m_results;
            }
            set
            {
                SetProperty(ref m_results, value);
            }
        }

        public ObservableCollection<StatisticsViewerWinUI.Model.DataSet> DataSetNames
        {
            get
            {
                return m_dataSetNames;
            }
            set
            {
                SetProperty(ref m_dataSetNames, value);
            }
        }
        #endregion

        #region Menu Command Handlers
        private async void FileOpen()
        {
            FileOpenPicker openPicker = new();

            var window = (Application.Current as App)?.Window as MainWindow;

            var hWnd = WinRT.Interop.WindowNative.GetWindowHandle(window);

            WinRT.Interop.InitializeWithWindow.Initialize(openPicker, hWnd);

            openPicker.ViewMode = PickerViewMode.List;
            openPicker.SuggestedStartLocation = PickerLocationId.ComputerFolder;
            openPicker.FileTypeFilter.Add(".txt");

            StorageFile file = await openPicker.PickSingleFileAsync();
            if (file != null)
            {
                string name = file.Name.Split('.')[0];

                List<double> data = new();

                foreach (string line in File.ReadAllLines(file.Path))
                {
                    data.Add(Double.Parse(line));
                }

                AddDataSet(name, data);

                // The view's data grid needs updating 
                WeakReferenceMessenger.Default.Send(new UpdateMessage());
            }
        }

        private void FileExit()
        {
            Application.Current.Exit();
        }

        private async Task<List<string>> GetDataSetsAsync(string title, int maxSelection)
        {
            List<string> selectedDataSets = new();

            DataSetSelectDialog dlgDataSets = new(this);
            dlgDataSets.SetMaxSelection(maxSelection);

            ContentDialog dialog = new();

            dialog.XamlRoot = App.MainRoot.XamlRoot;
            dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            dialog.Title = title;
            dialog.PrimaryButtonText = "OK";
            dialog.CloseButtonText = "Cancel";
            dialog.DefaultButton = ContentDialogButton.Primary;
            dialog.Content = dlgDataSets;

            var result = await dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                selectedDataSets = dlgDataSets.GetDataSetNames();
            }

            return selectedDataSets;
        }

        private async void StatisticsDescriptive()
        {
            try
            {
                List<string> selectedDataSets = await GetDataSetsAsync("Descriptive Statistics", 1);
                if (selectedDataSets.Count > 0)
                {
                    IList<double> data = m_dataManager.GetDataSet(selectedDataSets[0]);
                    IDictionary<string, double> results = m_statisticsOps.DescriptiveStatistics(data);
                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async void StatisticsLinearRegression()
        {
            try
            {
                List<string> selectedDataSets = await GetDataSetsAsync("Linear Regression", 2);
                if (selectedDataSets.Count > 0)
                {
                    IList<double> xs = m_dataManager.GetDataSet(selectedDataSets[0]);
                    IList<double> ys = m_dataManager.GetDataSet(selectedDataSets[1]);

                    IDictionary<string, double> results = m_statisticsOps.LinearRegression(xs, ys);

                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async Task<TTestParams> GetTTestParamsAsync(bool onlyMu)
        {
            TTestParams testParams = new();

            ContentDialog dialog = new();
            TTestParamsDialog dlg = new(onlyMu);

            dialog.XamlRoot = App.MainRoot.XamlRoot;
            dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            dialog.Title = "Test Parameters";
            dialog.PrimaryButtonText = "OK";
            dialog.CloseButtonText = "Cancel";
            dialog.DefaultButton = ContentDialogButton.Primary;
            dialog.Content = dlg;

            var result = await dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                testParams = dlg.GetParams();
            }

            testParams.IsSet = (result == ContentDialogResult.Primary) ? true : false;
            return testParams;
        }

        private async Task<FTestParams> GetFTestParamsAsync()
        {
            FTestParams testParams = new();

            ContentDialog dialog = new();
            FTestParamsDialog dlg = new();

            dialog.XamlRoot = App.MainRoot.XamlRoot;
            dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            dialog.Title = "Test Parameters";
            dialog.PrimaryButtonText = "OK";
            dialog.CloseButtonText = "Cancel";
            dialog.DefaultButton = ContentDialogButton.Primary;
            dialog.Content = dlg;

            var result = await dialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                testParams = dlg.GetParams();
            }

            testParams.IsSet = (result == ContentDialogResult.Primary) ? true : false;
            return testParams;
        }

        private async void SummaryDataTTest()
        {
            try
            {
                TTestParams testParams = await GetTTestParamsAsync(false);
                if(testParams.IsSet)
                {
                    TTest test = new(testParams.Mu0, testParams.X_bar, testParams.Sx, testParams.N);
                    test.Perform();

                    IDictionary<string, double> results = test.Results();

                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async void OneSampleTTest()
        {
            try
            {
                List<string> selectedDataSets = await GetDataSetsAsync("One-sample TTest", 1);
                if (selectedDataSets.Count > 0)
                {
                    IList<double> data = m_dataManager.GetDataSet(selectedDataSets[0]);

                    TTestParams testParams = await GetTTestParamsAsync(true);
                    if (testParams.IsSet)
                    {
                        TTest test = new(testParams.Mu0, data);
                        test.Perform();

                        IDictionary<string, double> results = test.Results();

                        PopulateResults(results);
                    }
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async void TwoSampleTTest()
        {
            try
            {
                List<string> selectedDataSets = await GetDataSetsAsync("Two-sample TTest", 2);
                if (selectedDataSets.Count > 0)
                {
                    IList<double> _x1 = m_dataManager.GetDataSet(selectedDataSets[0]);
                    IList<double> _x2 = m_dataManager.GetDataSet(selectedDataSets[1]);

                    Dictionary<string, IList<double>> data = new()
                    {
                        ["x1"] = _x1,
                        ["x2"] = _x2
                    };
                    TTest test = new(data);
                    test.Perform();

                    IDictionary<string, double> results = test.Results();

                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async void SummaryDataFTest()
        {
            try
            {
                FTestParams testParams = await GetFTestParamsAsync();
                if (testParams.IsSet)
                {
                    FTest test = new(testParams.Sx1, testParams.Sx2, testParams.N1, testParams.N2);
                    test.Perform();
                    IDictionary<string, double> results = test.Results();

                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private async void TwoSampleFTest()
        {
            try
            {
                List<string> selectedDataSets = await GetDataSetsAsync("Two-sample FTest", 2);
                if (selectedDataSets.Count > 0)
                {
                    IList<double> _x1 = m_dataManager.GetDataSet(selectedDataSets[0]);
                    IList<double> _x2 = m_dataManager.GetDataSet(selectedDataSets[1]);

                    FTest test = new(_x1, _x2);
                    test.Perform();

                    IDictionary<string, double> results = test.Results();

                    PopulateResults(results);
                }
            }
            catch (Exception e)
            {
                ReportException(e);
            }
        }

        private void SetDarkTheme()
        {
            // Save theme choice to LocalSettings. 
            // ApplicationTheme enum values: 0 = Light, 1 = Dark
            DarkMode = true;
            ApplicationData.Current.LocalSettings.Values["themeSetting"] = 1;
        }

        private void SetLightTheme()
        {
            DarkMode = false;
            ApplicationData.Current.LocalSettings.Values["themeSetting"] = 0;
        }

        private void HelpAbout()
        {
            ContentDialog dialog = new();

            dialog.XamlRoot = App.MainRoot.XamlRoot;
            dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            dialog.Title = "About StatisticsViewer";
            dialog.PrimaryButtonText = "OK";
            dialog.DefaultButton = ContentDialogButton.Primary;
            dialog.Content = new AboutDialog();

            var result = dialog.ShowAsync();
        }

        private void ResultsCopy()
        {
            StringBuilder sb = new StringBuilder();
            foreach (var result in m_results)
            {
                sb.AppendLine($"{result.Name}\t{result.Value}");
            }

            DataPackage dataPackage = new DataPackage();
            dataPackage.RequestedOperation = DataPackageOperation.Copy;
            dataPackage.SetText(sb.ToString());
            Clipboard.SetContent(dataPackage);
        }

        #endregion

        #region Private Functions
        private void AddDataSet(string name, List<double> data)
        {
            m_dataManager.Add(name, data);
            StatisticsDescriptiveCommand.NotifyCanExecuteChanged();

            m_dataSetNames.Clear();
            var dataSets = m_dataManager.ListDataSets();
            foreach (StatisticsLibraryWRC.DataSet dataSet in dataSets)
            {
                StatisticsViewerWinUI.Model.DataSet ds = new();
                ds.Name = dataSet.Name;
                m_dataSetNames.Add(ds);
            }

            PopulateData();
        }

        private int GetMaxLength()
        {
            var dataSets = m_dataManager.ListDataSets();
            int length = 0;
            foreach (StatisticsLibraryWRC.DataSet dataSet in dataSets)
            {
                length = Math.Max((int)dataSet.Size, length);
            }
            return length;
        }

        private void PopulateData()
        {
            DataTable dataTable = new();
            dataTable.Columns.Add(new DataColumn() { ColumnName = "RowObject" }); // add column to store original row object

            int maxrows = GetMaxLength();
            var dataSets = m_dataManager.ListDataSets();
            int ncols = dataSets.Count;

            // add columns to datatable
            for (int col = 0; col < ncols; col++)
            {
                // add corresponding column to datatable
                StatisticsLibraryWRC.DataSet dataSet = (StatisticsLibraryWRC.DataSet)dataSets[col];
                dataTable.Columns.Add(new DataColumn() { ColumnName = dataSet.Name });
            }

            for (int row = 0; row < maxrows; row++)
            {
                // create new datatable row
                DataRow dataRow = dataTable.NewRow();

                // add data from each column in the row to the datatable row
                for (int col = 0; col < ncols; col++)
                {
                    StatisticsLibraryWRC.DataSet dataSet = (StatisticsLibraryWRC.DataSet)dataSets[col];
                    IList<double> data = m_dataManager.GetDataSet(dataSet.Name);

                    // add column value to row
                    int data_size = data.Count;
                    if(row < data_size)
                    {
                        dataRow[col] = data[row];
                    }
                    else
                    {
                        dataRow[col] = null; // insert null if the table has columns defined for which there is no data in the dataset
                    }
                }

                // add datable row to datatable
                dataTable.Rows.Add(dataRow);
            }

            // convert datatable to collection of 'object'
            m_dataCollection = new ObservableCollection<object>();

            foreach (DataRow row in dataTable.Rows)
                m_dataCollection.Add(row.ItemArray);
        }

        private void PopulateResults(IDictionary<string, double> results)
        {
            m_results.Clear();

            foreach (var result in results)
            {
                m_results.Add(new ResultStatistic(result.Key, result.Value));
            }

            ResultsCopyCommand.NotifyCanExecuteChanged();
        }

        // Generic exception reporting
        private async void ReportException(Exception e)
        {
            ContentDialog dialog = new();

            dialog.XamlRoot = App.MainRoot.XamlRoot;
            dialog.Style = Application.Current.Resources["DefaultContentDialogStyle"] as Style;
            dialog.Title = "Exception Report";
            dialog.PrimaryButtonText = "OK";
            dialog.DefaultButton = ContentDialogButton.Primary;
            dialog.Content = new ExceptionDialog(e);

            var result = await dialog.ShowAsync();
        }
        #endregion
    }
}
