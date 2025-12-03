# ViewportObjectDetectionPlugin

Copyright (c) 2025 Justin Gilbert (AkumaVenom)

A high-performance C++ plugin that provides YOLO-style simulated object detection for NPCs in Unreal Engine 5.5.
Actors can be marked with Detectable Components, and NPCs use Detector Components to scan their environment in real time, producing structured detection results and LLM-friendly context text.

The system allows full customization of what information is included in each scan result — such as labels, descriptions, tags, distances, confidence values, and any additional metadata you choose to expose through Detectable Components.
Control exactly what data your NPCs see.

Includes:

- Cone-based vision scanning with optional line-of-sight

- Detectable components with name, description, and tags

- Blueprint-exposed detection results

- Automatic LLM context string generation

- Debug visualization (PIE + packaged)

- Perfect for AI-driven games requiring NPC perception, narrative reasoning, or LLM-powered behavior systems.

=========================================================================

✅ Step-by-Step Guide IMPORTANT (Disable CaptureData Plugin)

1. Close Unreal Engine completely

Make sure no UE editor or project is open.

2. Open the CaptureData.uplugin file as Administrator

Navigate to: C:\Program Files\Epic Games\UE_5.5\Engine\Plugins\VirtualProduction\CaptureData\

Right-click open CaptureData.uplugin with Notepad or VS Code → Run as administrator,

3. Disable Sub-Plugins

Inside CaptureData you will see a Plugins array:

---

"Plugins":

"Name": "ImgMedia",
"Enabled": true

"Name": "CameraCalibrationCore",
"Enabled": true

---

Make sure all enabled entries are set to false if they aren't already.

This ensures UE does not load any CaptureData-related content that conflict with this plugin.

4. Save the file and reopen your project

Unreal Engine should now launch compile the plugin C++ modules without it trying to rebuild the broken CaptureData plugin.
