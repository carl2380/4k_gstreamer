#!/bin/bash

# Update package list and install GStreamer and its plugins
sudo apt-get update
sudo apt-get install -y gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-gl

# Install additional dependencies if needed
# sudo apt-get install -y <additional-dependencies>

# Set up environment variables if necessary
# export GST_PLUGIN_PATH=/usr/lib/gstreamer-1.0

echo "Setup complete. You can now build and run the project."