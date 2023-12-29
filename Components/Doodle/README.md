## FILE OVERVIEW

## Doodle.cpp

**Purpose:** Implements the core functionality of a Doodle, a drawable window in the application.

**Key Features:**
- Window Management: Handles creation and destruction of a Doodle window.
- Cursor Customization: Loads custom cursors (pencil, eraser) and updates cursor state based on user interactions.
- Rendering: Manages the rendering process of the Doodle window, including handling ImGui window flags and styles.
- Drawing Mechanics: Facilitates drawing operations on the canvas, including handling straight line drawing and erasing.
- User Interaction: Responds to user inputs such as mouse clicks and movements, updates the canvas accordingly.
- Context Menu: Provides a context menu for user actions like clearing the canvas, changing modes, and customizing colors.

## Doodle.h

**Purpose:** Declares the Doodle class and its properties.

**Key Features:**
- Class Structure: Defines the structure of a Doodle window including methods for rendering, handling drawing, and managing window state.
- Canvas Management: Manages canvas properties such as size, color, and aspect ratio.
- Cursor Handling: Includes methods for updating and managing different cursors.

## DoodleManager.cpp

**Purpose:** Manages multiple Doodle windows within the application.

**Key Features:**
- Window Creation: Facilitates the creation of new Doodle windows.
- Window Rendering: Manages the rendering process of all Doodle windows.
- Window Positioning: Controls the positioning of new Doodle windows for a cascading window effect.

## DoodleManager.h

**Purpose:** Declares the DoodleManager class and its properties.

**Key Features:**
- Doodle Window Management: Handles the collection of Doodle windows and provides methods for their management.
- Destruction Logic: Contains logic for proper clean-up and destruction of Doodle windows.
