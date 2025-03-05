# Jetson GStreamer App

This project is designed to capture 4K video from a Raspberry Pi camera using GStreamer on the Jetson Orin NX platform. The captured video is displayed using `glimagesink`.

## Project Structure

```
jetson-gstreamer-app
├── src
│   ├── main.cpp          # Main application code
│   └── CMakeLists.txt   # CMake configuration for the source directory
├── CMakeLists.txt       # Top-level CMake configuration
├── README.md            # Project documentation
└── scripts
    └── setup.sh         # Setup script for environment configuration
```

## Dependencies

- Jetson Orin NX
- Raspberry Pi Camera
- GStreamer (with necessary plugins for video capture and OpenGL)

## Setup Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/jetson-gstreamer-app.git
   cd jetson-gstreamer-app
   ```

2. **Run the setup script:**
   This script will install the necessary dependencies and configure the environment.
   ```bash
   chmod +x scripts/setup.sh
   ./scripts/setup.sh
   ```

3. **Build the project:**
   Use CMake to build the application.
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage

To run the application, execute the following command from the `build` directory:
```bash
./jetson-gstreamer-app
```

This will start capturing 4K video from the Raspberry Pi camera and display it using `glimagesink`.

## Troubleshooting

- Ensure that the Raspberry Pi camera is properly connected and enabled.
- Verify that GStreamer is installed with the required plugins.
- Check for any error messages in the terminal for guidance on resolving issues.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.