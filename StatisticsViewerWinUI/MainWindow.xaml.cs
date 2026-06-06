using Microsoft.UI.Xaml;
using System;
using System.IO;

using Windows.UI.ViewManagement;

using WinUIEx;

namespace StatisticsViewerWinUI
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();

            AppWindow.SetIcon(Path.Combine(AppContext.BaseDirectory, "Assets/WindowIcon.ico"));
            Content = null;
            Title = "Statistics Viewer (WinUI)";

            AppWindow.Resize(new Windows.Graphics.SizeInt32 { Width = 800, Height = 700 });
        }
    }
}
