# ofxWebcam

smooth webcam using OpenCV VideoCapture

Tested on oF 0.12.0

## Why not ofVideoGrabber?

Default `ofVideoGrabber` webcam is very slow on Windows 10/11 when high resolution (for example 5-10 FPS if 1080p/720p, maybe because of DirectShow).

## Dependencies

- ofxOpenCv
- [ofxCv](https://github.com/kylemcdonald/ofxCv)
- [ofxAsync](https://github.com/funatsufumiya/ofxAsync)

## Known Issues

- on macOS, you may need to run your app twice for Camera Security.

## License

0BSD or/and WTFPL (for source codes)

> [!Warning]

> Please note that [`libs/opencv/lib/osx`](libs/opencv/lib/osx) folder contains OpenCV/FFmpeg dylibs. These have different licenses such as LGPL-2.1 (see https://opencv.org/license/ and https://ffmpeg.org/legal.html).
