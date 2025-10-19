# ofxWebcam

smooth webcam using OpenCV VideoCapture

Tested on oF 0.12.0

## Dependencies

- ofxOpenCv
- [ofxCv](https://github.com/kylemcdonald/ofxCv)
- [ofxAsync](https://github.com/funatsufumiya/ofxAsync)

## Why

Default `ofVideoGrabber` webcam is very slow on recent Windows 11 when high resolution (maybe because of DirectShow).

## Known Issues

- on macOS, you may need to run your app twice for Camera Security.

## License

0BSD or/and WTFPL (for source codes)

> [!Warning]
> Please note that [`libs/opencv/lib/osx`](libs/opencv/lib/osx) folder contains OpenCV/FFmpeg dylibs. These have different licenses such as LGPL-2.1 (see https://opencv.org/license/ and https://ffmpeg.org/legal.html).