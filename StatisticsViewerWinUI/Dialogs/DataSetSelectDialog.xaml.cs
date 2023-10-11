using Microsoft.UI.Xaml.Controls;

using System.Collections.Generic;

using StatisticsViewerWinUI.ViewModels;

namespace StatisticsViewerWinUI.Dialogs
{
    public sealed partial class DataSetSelectDialog : Page
    {
        private int m_maxSelection = 0;

        public DataSetSelectDialog(MainViewModel viewModel)
        {
            ViewModel = viewModel;

            this.InitializeComponent();
        }
        public MainViewModel ViewModel
        {
            get;
        }

        public void SetMaxSelection(int maxSelection) 
        { 
            m_maxSelection = maxSelection; 
        }

        public List<string> GetDataSetNames()
        {
            List<string> dataSetNames = new List<string>();
            foreach (StatisticsViewerWinUI.Model.DataSet item in lvDataSets.SelectedItems)
            {
                dataSetNames.Add(item.Name);
            }
            return dataSetNames;
        }

        private void lvDataSets_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (lvDataSets.SelectedItems.Count > m_maxSelection)
            {
                lvDataSets.SelectedItems.RemoveAt(0);
            }
        }
    }
}
