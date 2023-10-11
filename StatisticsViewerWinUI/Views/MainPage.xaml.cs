using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;

using CommunityToolkit.WinUI.UI.Controls;

using StatisticsViewerWinUI.ViewModels;
using CommunityToolkit.Mvvm.DependencyInjection;
using CommunityToolkit.Mvvm.Messaging;
using Windows.Storage;

namespace StatisticsViewerWinUI.Views
{
    public sealed partial class MainPage : Page, IRecipient<UpdateMessage>
    {
        public MainViewModel ViewModel { get; set; }

        public MainPage()
        {
            InitializeComponent();

            ViewModel = Ioc.Default.GetService<MainViewModel>();

            WeakReferenceMessenger.Default.Register<UpdateMessage>(this);
        }

        public void Receive(UpdateMessage message)
        {
            UpdateData();
        }

        private void UpdateData()
        {
            dataGrid.Columns.Clear();

            var dataSets = ViewModel.ListDataSets();
            int ncols = dataSets.Count;

            for (int col = 0; col < ncols; col++)
            {
                StatisticsLibraryWRC.DataSet dataSet = (StatisticsLibraryWRC.DataSet)dataSets[col];
                // Add column to datagrid using the correct header label. Bind using index of array.
                dataGrid.Columns.Add(new DataGridTextColumn()
                {
                    Header = dataSet.Name,
                    Binding = new Binding() { Path = new PropertyPath("[" + col.ToString() + "]") }
                });
            }

            dataGrid.ItemsSource = ViewModel.Collection;
        }

        private void ToggleSwitch_Toggled(object sender, RoutedEventArgs e)
        {
            ToggleSwitch toggleSwitch = sender as ToggleSwitch;
            if (toggleSwitch != null)
            {
                if (toggleSwitch.IsOn == true)
                {
                    if (this.Content is FrameworkElement frameworkElement)
                    {
                        frameworkElement.RequestedTheme = ElementTheme.Dark;
                    }
                }
                else
                {
                    if (this.Content is FrameworkElement frameworkElement)
                    {
                        frameworkElement.RequestedTheme = ElementTheme.Light;
                    }
                }
            }

            ApplicationData.Current.LocalSettings.Values["themeSetting"] = ((ToggleSwitch)sender).IsOn ? 0 : 1;
        }

        private void ToggleSwitch_Loaded(object sender, RoutedEventArgs e)
        {
            if (ApplicationData.Current.LocalSettings.Values.TryGetValue("themeSetting", out object themeSetting) && 
                (int)themeSetting == 0)
            {
                //dark_switch.IsOn = true;
            }
            else
            {
                //dark_switch.IsOn = false;
            }
        }

    }
}
