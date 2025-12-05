# ViewportObjectDetectionPlugin

Copyright (c) 2025 Justin Gilbert (AkumaVenom)

-------------------------------------------------------------------------------------------------

![Main](https://github.com/user-attachments/assets/b48070b3-5cf9-495f-a2e2-de37231496b4)

![main2](https://github.com/user-attachments/assets/e2223e1a-655b-4823-aa02-e17a0dd2897e)

-------------------------------------------------------------------------------------------------

Viewport Object Detection Plugin

Component-based, fully customizable “AI vision” for Unreal Engine — with YOLO-style HUD

The Viewport Object Detection Plugin lets you turn any Actor or Pawn into a “detector” that scans the scene and returns a list of rich, text-driven detections you define yourself.

There are no external AI models here — you control exactly what gets detected and what text is exposed (name, description, tags, category). Perfect for:

Feeding LLM-driven NPCs contextual info about what they “see”

Building cyberpunk scanners, AR vision, detective modes

Debugging perception and gameplay logic with visual overlays

Everything is component-based, Blueprint-exposed, and designed for high performance in UE 5.5.

-------------------------------------------------------------------------------------------------

✨ Feature Summary

✅ Component-based object detection (no ML AI dependency)

✅ Completely customizable labels, descriptions, categories, and tags from detections

✅ Viewport/trace-driven detection for cameras, players, and NPCs

✅ Fully Blueprint-exposed structs and functions

✅ YOLO-style UMG HUD with bounding boxes and header text

✅ Distance-scaled box sizing

✅ Written in performant C++ with easy Blueprint integration

✅ Perfect foundation for LLM-driven AI, scanners, AR overlays, and debugging

-------------------------------------------------------------------------------------------------

![1](https://github.com/user-attachments/assets/3d62dd03-0e35-4d52-989a-745a2b63f1fe)

![2](https://github.com/user-attachments/assets/253a5876-19d0-442c-af24-3622bd321f92)

![3](https://github.com/user-attachments/assets/60729b73-4fc6-4aa3-aeef-9a6080d9c4b2)

![4](https://github.com/user-attachments/assets/522fdfc6-d9dc-4592-a4fe-130d3801c31e)

<img width="1278" height="743" alt="5" src="https://github.com/user-attachments/assets/d600a6d8-5c57-421d-81aa-9ac998e0991c" />

-------------------------------------------------------------------------------------------------

💡 Core Idea: You Define What “Detection” Means

Every object you want to show up in “AI vision” gets a Detectable Object Component where you define:

Display Name – e.g. “A Young Woman”, “Neon Vending Machine”

Description – rich text used for LLMs or UI, e.g.
“You see a young woman in a futuristic cyberpunk outfit with dark hair and a heart tattoo on her cheek.”

Category – e.g. Character, Enemy, Item, PointOfInterest, Prop

Tags / Keywords – arbitrary strings for filtering, grouping, or LLM prompts

Optional extra metadata for your own systems

When a detector scans, it returns a list of FViewportDetectionResult structs that include:

World location

Screen position

Distance

Forward dot (how centered it is in view)

Confidence (simulated)

Your label, description, category, tags

The plugin never guesses — it just exposes exactly what you authored.

-------------------------------------------------------------------------------------------------

🧩 Main Components
UDetectableObjectComponent

Attach this to any Actor/Pawn that should be detectable.

Editable properties:

Display Name (Text)

Description (Text)

Category (Enum)

Tags (Array of FName or String)

Drives:

What LLMs / HUD see

How objects can be filtered in scans (by category, tag, distance, etc.)

-------------------------------------------------------------------------------------------------

UObjectDetectorComponent

Attach this to the player, a camera, or an NPC to make it perform viewport scans.

Performs viewport / trace-based detection every scan

Returns an array of FViewportDetectionResult

Supports:

AutoScan (tick-based) or manual ScanNow()

Distance and FOV limits

Filtering by category / tags / line of sight

100% Blueprint-exposed for setups like:

“Scan every 0.3s while aiming”

“Only detect Characters and Items”

“Only feed detections in front of the camera to the LLM”

-------------------------------------------------------------------------------------------------

USimObjectDetectionSubsystem

Engine subsystem that simulates an AI object detection pipeline:

Gathers all UDetectableObjectComponent instances

Applies filtering and visibility logic

Provides a central location to query detections from C++ or Blueprints

This is the backbone that replaces real ML with deterministic, designer-defined detection.

-------------------------------------------------------------------------------------------------

UDetectionHUDComponent

Optional helper that connects detection data to a HUD.

Listens for detector results

Broadcasts them to a UMG HUD (e.g. WBP_DetectionHUD)

Handles:

Events when detections change

Packaging/editor differences for screen coordinates

-------------------------------------------------------------------------------------------------

🖼️ Built-In YOLO-Style HUD (UMG)

The plugin ships with ready-to-use widgets under the plugin’s Content folder so they work in both editor and packaged builds.

WBP_DetectionHUD

Master overlay widget that:

Receives an array of FViewportDetectionResult

Projects each detection into screen space

Spawns one WBP_DetectionBox per detection

Clears and rebuilds boxes each update

Scales box size based on distance

Corrects for editor vs packaged viewport differences (2.0 / 2.2 factor)

Works in PIE, Standalone, and fully packaged builds

WBP_DetectionBox

A single detection box widget:

YOLO-style rectangle with solid header bar

Displays the Display Name from the Detectable Object Component

Box color can be driven by Category (e.g.:

Character = green

Enemy = red

Item = blue

POI = cyan)

No textures required — pure UMG for easy theming

You can fully restyle these or swap them out while still using the core detection logic.

-------------------------------------------------------------------------------------------------

🧠 Designed for LLM / NPC Integration

Because each detection carries human-readable text, wiring it into an LLM is trivial.

Example pseudo-flow:

1. Detector scans viewport → gets Detections array

2. You build a descriptive string like:

“You see: [Name] – [Description]. Category: [Category]. Tags: [Tags]. Distance: [X] meters.”

3. Feed that into your NPC’s LLM prompt as “things currently visible”

4. Let the NPC reason / speak based on what they “see”

You remain in full control of:

- How verbose descriptions are

- What categories matter

- Which tags carry gameplay meaning

-------------------------------------------------------------------------------------------------

🚀 Quick Start
1. Mark objects as detectable

Open an Actor or NPC Blueprint

Add DetectableObjectComponent

Set:

Display Name

Description

Category

Tags

2. Add a detector to your player / camera

Open your player, pawn, or camera Blueprint

Add ObjectDetectorComponent

Configure:

AutoScan (on/off)

Scan interval / range / FOV

Category / tag filters as needed

3. Add the HUD

On BeginPlay:

Create Widget → Class = WBP_DetectionHUD

Add to Viewport

Store a reference

Bind from UDetectionHUDComponent (or directly from detector) to:

Call UpdateDetections(DetectionsArray) on WBP_DetectionHUD

Hit Play — you should see YOLO-style boxes popping up over detectable actors.

-------------------------------------------------------------------------------------------------

🧑‍💻 Author

Justin Gilbert / AkumaVenom

If this plugin helps you, please consider ⭐ starring the repo or sharing it.

Donation/Tips https://www.paypal.me/akumacreative

AkumaVenom's Discord: https://discord.gg/Uf8Q8usSmk

-------------------------------------------------------------------------------------------------

⚠️ IMPORTANT Guide (Disable CaptureData Plugin)

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

-------------------------------------------------------------------------------------------------
