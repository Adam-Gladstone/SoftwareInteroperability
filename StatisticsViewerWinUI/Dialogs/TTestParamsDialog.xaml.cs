using Microsoft.UI.Xaml.Controls;

using StatisticsViewerWinUI.Model;

namespace StatisticsViewerWinUI.Dialogs
{
    public sealed partial class TTestParamsDialog : Page
    {
        public TTestParamsDialog(bool onlyMu)
        {
            this.InitializeComponent();

            numberMu0.IsEnabled = true;
            numberXbar.IsEnabled = !onlyMu;
            numberSx.IsEnabled = !onlyMu;
            numberN.IsEnabled = !onlyMu;
        }

        public TTestParams GetParams()
        {
            TTestParams testParams = new TTestParams();

            testParams.Mu0 = numberMu0.Value;
            testParams.X_bar = numberXbar.Value;
            testParams.Sx = numberSx.Value;
            testParams.N = numberN.Value;

            return testParams;
        }
    }
}
