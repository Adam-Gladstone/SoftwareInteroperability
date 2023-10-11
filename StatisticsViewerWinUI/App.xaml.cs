using System;
using Windows.ApplicationModel;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;

using StatisticsViewerWinUI.Views;
using CommunityToolkit.Mvvm.DependencyInjection;
using StatisticsViewerWinUI.ViewModels;
using Microsoft.Extensions.DependencyInjection;

using StatisticsLibraryWRC;
using Windows.Storage;

namespace StatisticsViewerWinUI
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        public static FrameworkElement MainRoot { get; private set; }

        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();

            // Get theme choice from LocalSettings.
            object value = ApplicationData.Current.LocalSettings.Values["themeSetting"];
            if (value != null)
            {
                // Apply theme choice.
                App.Current.RequestedTheme = (ApplicationTheme)(int)value;
            }
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        protected override void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
        {
            m_window = new MainWindow();

            Ioc.Default.ConfigureServices(new ServiceCollection()
                .AddSingleton<DataManager>()
                .AddSingleton<Statistics>()
                .AddTransient<MainViewModel>()
                .BuildServiceProvider()
                );

            Frame rootFrame = CreateRootFrame();
            if (rootFrame.Content == null)
            {
                rootFrame.Navigate(typeof(MainPage), args.Arguments);
            }

            m_window.Activate();

            MainRoot = Window.Content as FrameworkElement;
        }

        Frame CreateRootFrame()
        {
            Frame rootFrame = null;

            var content = m_window.Content;
            if (content != null)
            {
                rootFrame = (Frame)content;
            }

            // Don't repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                // Create a Frame to act as the navigation context
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                // Place the frame in the current Window
                m_window.Content = rootFrame;
            }

            return rootFrame;
        }

        /// <summary>
        /// Invoked when Navigation to a certain page fails
        /// </summary>
        /// <param name="sender">The Frame which failed navigation</param>
        /// <param name="e">Details about the navigation failure</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }

        internal Window m_window;
        public Window Window => m_window;
    }
}
