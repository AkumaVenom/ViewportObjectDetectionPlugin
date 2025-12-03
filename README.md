# ViewportObjectDetectionPlugin

Copyright (c) 2025 Justin Gilbert (AkumaVenom)

============================================================================================

Fully Dynamic YOLO-style UI Vision Preview:

<img width="3839" height="2159" alt="Screenshot 2025-12-04 093211" src="https://github.com/user-attachments/assets/6e55edfe-d668-4619-a0fe-081765a3e405" />

============================================================================================

A high-performance C++ plugin that provides YOLO-style simulated object detection for NPCs in Unreal Engine 5.5.
Actors can be marked with Detectable Components, and NPCs use Detector Components to scan their environment in real time, producing structured detection results and LLM-friendly context text.

The system allows full customization of what information is included in each scan result — such as labels, descriptions, tags, distances, confidence values, and any additional metadata you choose to expose through Detectable Components.
Control exactly what data your NPCs see.

This Plugin also introduces a complete real-time detection overlay system, bringing fully dynamic YOLO-style UI vision to Unreal Engine. The v2.0 compiled plugin now includes built-in UI widgets and a ready-to-use detection HUD component that renders clean, scalable bounding boxes for all detected objects.

Includes:

- Cone-based vision scanning with optional line-of-sight

- Detectable components with name, description, and tags

- Blueprint-exposed detection results

- fully dynamic real-time YOLO-style UI Overlay System

- Automatic LLM context string generation

- Debug visualization (PIE + packaged)

- Perfect for AI-driven games requiring NPC perception, narrative reasoning, or LLM-powered behavior systems.

=========================================================================

Plugin Created By Justin Gilbert / AkumaVenom

Donation/Tips https://www.paypal.me/akumacreative

AkumaVenom's Discord: https://discord.gg/Uf8Q8usSmk

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
