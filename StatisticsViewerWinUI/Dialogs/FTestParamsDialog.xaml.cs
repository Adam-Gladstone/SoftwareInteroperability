using Microsoft.UI.Xaml.Controls;

using StatisticsViewerWinUI.Model;

namespace StatisticsViewerWinUI.Dialogs
{
    public sealed partial class FTestParamsDialog : Page
    {
        public FTestParamsDialog()
        {
            this.InitializeComponent();
        }

        public FTestParams GetParams()
        {
            FTestParams testParams = new FTestParams();

            testParams.Sx1 = numberSx1.Value;
            testParams.N1 = numberN1.Value;
            testParams.Sx2 = numberSx2.Value;
            testParams.N2 = numberN2.Value;

            return testParams;
        }
    }
}
