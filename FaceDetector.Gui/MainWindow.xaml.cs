using System;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace FaceDetector.Gui
{
    /// <summary>
    ///     Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ManagedImage cameraBuffer;
        private CameraWrapper cameraWrapper;

        private FaceDetectorWrapper detector;
        private readonly object mutex = new object();

        private bool shouldStop;

        public MainWindow()
        {
            InitializeComponent();
        }

        public static string AssemblyDirectory
        {
            get
            {
                var codeBase = Assembly.GetExecutingAssembly().CodeBase;
                var uri = new UriBuilder(codeBase);
                var path = Uri.UnescapeDataString(uri.Path);
                return Path.GetDirectoryName(path);
            }
        }

        private void DrawDetection(ManagedImage bitmap)
        {
            var detections = detector.detect(bitmap);
            Application.Current.Dispatcher.BeginInvoke(new Action(() =>
            {
                var imageSource = BitmapSource.Create(bitmap.width, bitmap.height, 96, 96, PixelFormats.Bgr24, null,
                    bitmap.data, bitmap.step);


                var target = new RenderTargetBitmap(bitmap.width, bitmap.height, 96, 96, PixelFormats.Pbgra32);
                var visual = new DrawingVisual();

                using (var r = visual.RenderOpen())
                {
                    r.DrawImage(imageSource, new Rect(0, 0, bitmap.width, bitmap.height));
                    foreach (var detection in detections)
                    {
                        var rec = new Rect(detection.x, detection.y, detection.width, detection.height);
                        r.DrawRectangle(null, new Pen(Brushes.Red, 5.0), rec);
                        r.DrawText(
                            new FormattedText($"{detection.confidence * 100:F1}%", CultureInfo.InvariantCulture,
                                FlowDirection.LeftToRight, new Typeface("Arial"), 20, Brushes.Red),
                            new Point(detection.x + detection.width - 60, detection.y - 20));
                    }
                }

                target.Render(visual);

                CameraOutput.Source = target;
            }), DispatcherPriority.Normal);
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            var directory = AssemblyDirectory;
            detector = new FaceDetectorWrapper(
                directory + "/Model/opencv_face_detector.pbtxt",
                directory + "/Model/opencv_face_detector_uint8.pb");

            cameraWrapper = new CameraWrapper();
            var size = cameraWrapper.getFrameSize();
            cameraBuffer = new ManagedImage(size);

            Task.Run(() =>
                {
                    while (true)
                        lock (mutex)
                        {
                            if (shouldStop) break;
                            cameraWrapper.readFrame(cameraBuffer);
                            DrawDetection(cameraBuffer);
                        }
                }
            );
        }

        private void MainWindow_OnClosing(object sender, CancelEventArgs e)
        {
            lock (mutex)
            {
                shouldStop = true;
            }
        }
    }
}