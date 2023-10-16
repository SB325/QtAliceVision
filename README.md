# QtAliceVision - AliceVision/OIIO plugin for Qt

QtAliceVision is a C++ plugin providing: 
  - classes to load and visualize AliceVision and Alembic data through QML
  - an [OpenImageIO](http://github.com/OpenImageIO/oiio) backend for image IO in Qt.

Currently available:
  - [X] Features Viewer
    - Position, scale and orientation 
    - Status: extracted, matched or reconstructed 
  - [ ] Matches Viewer
  - [X] Statistics 
    - Per view statistics with reprojection error, observations histograms 
    - Global SfM statistics with number of landmarks/matches, reprojection errors, observations per view 
  - [X] Float Image Viewer
    - Visualize images with floating point precision 
    - Dynamically adjust gain and gamma
  - [X] 3D Depth Maps
    - Visualize depth/sim maps generated by the [AliceVision](https://github.com/alicevision/AliceVision) framework in a 3D viewer
  - [X] Alembic 3D visualization
    - Point clouds
    - Cameras
  - [X] OIIO backend
    - Read RAW images from DSLRs
    - Read intermediate files of the [AliceVision](https://github.com/alicevision/AliceVision) framework stored in EXR format


## License

The project is released under MPLv2, see [**COPYING.md**](COPYING.md).


## Get the project

Get the source code:
```bash
git clone --recursive git://github.com/alicevision/QtAliceVision
cd QtAliceVision
```
See [**INSTALL.md**](INSTALL.md) to build and install the project.


## Usage

### AliceVision data visualization

Once built and with the plugin installation folder in `QML2_IMPORT_PATH`:

 - Create an `MSfMData` object to get access to the SfM information:

```js
import AliceVision 1.0

MSfMData {
  id: sfmData
  sfmDataPath: "/path/to/SfM/sfmData.abc”
}
```

 - Create an `MTracks` to load all matches and get access to tracks information:

```js
import AliceVision 1.0

MTracks {
  id: tracks
  matchingFolder: "/path/to/FeatureMatching/UID/”
}
```

 - Create a `FeaturesViewer` to visualize features position, scale, orientation and optionally information about the feature status regarding tracks and SfmData.

```js
FeaturesViewer {
  colorOffset: 0
  describerType: "sift"
  featureFolder: "/path/to/features/folder"
  mTracks: tracks
  viewId: 101245654
  color: “blue”
  landmarkColor: “red”
  displayMode: FeaturesViewer.Points
  mSfmData: sfmData
}
```

 - Create an `MSfMDataStats` to display global statistics about your SfMData:

```js

MSfMDataStats {
  msfmData: msfmData
  mTracks: mTracks
}
```

 - Create an `MViewStats` to display statistics about a specific View of your SfMData:

```js
MViewStats {
  msfmData: msfmData
  viewId: 451244710
}
```

 - Create a `FloatImageViewer` to display an image with floating point precision, allowing to dynamically adjust the gain and gamma:

```js
FloatImageViewer {
  source: "/path/to/image"
  gamma: 1.0
  gain: 1.0
  width: textureSize.width || 500
  height: textureSize.height || 500
  channelMode: "RGB" 
}
```

 - Create a `DepthMapEntity` to display a depth map as a point cloud in a 3D viewer:

```js
import DepthMapEntity 1.0

Scene3D {
  DepthMapEntity {
    source: "depthmap.exr"
  }
}
```

 - Create a `AlembicEntity` to display .abc point clouds and cameras in a 3D viewer:

```js
import AlembicEntity 1.0

Scene3D {
  AlembicEntity {
    source: "myfile.abc"
  }
}
```

 - Create a `SfmDataEntity` to display point clouds (in .abc, .sfm or .json format) and cameras in a 3D viewer:

```js
import SfmDataEntity 1.0

Scene3D {
  SfmDataEntity {
    source: "/path/to/pointcloud.sfm"
  }
}

```

### OpenImageIO backend

When added to the `QT_PLUGIN_PATH`, all supported image files will be loaded through this plugin.
