# RavenEngine Project

## Overview

We are developing a game engine to rival established engines such as Unreal, Unity, and Godot. Our engine will incorporate the standard features found in these engines, but with a unique additions and variation.

## RavenUI
RavenUI for visual UI creation.

### Components of RavenUI

RavenUI will need to include the following UI components:

- **Buttons:** Interactive elements for user input. These can trigger actions or events when clicked.

- **Textboxes:** Input fields for text entry. Users can type text or numbers into these fields.

- **Images:** Displaying visual content. Images can be used for icons, backgrounds, or other graphical elements.

- **Panels:** Containers for organizing UI elements. Panels help group related UI components together for layout purposes.

- **Lists:** Displaying collections of items. Lists can be used for things like inventory screens or character selection menus.

- **Scrollbars:** Navigating through scrollable content. Scrollbars are essential for UIs with more content than can fit on the screen at once.

- **Dropdowns:** Selecting options from a list. Dropdowns allow users to choose from a list of items.

- **Sliders:** Adjusting values within a range. Sliders are useful for settings or adjustments like volume controls.

- **Checkboxes:** Toggling options on/off. They are often used for enabling or disabling specific features or settings.

- **Radio buttons:** Selecting a single option from a group. Radio buttons are typically used when users need to choose only one option from a set of choices.

### Core UI Features of RavenUI

In addition to these UI components, RavenUI should also incorporate the following core UI-related features:

- **Widget System:** A core system for creating and managing UI widgets, including buttons, text fields, images, and custom widgets.

- **Layout Management:** A system for arranging and positioning widgets within the UI, supporting various layout strategies like grids, stacks, and anchors.

- **Styling and Theming:** Support for defining the visual appearance of widgets, including fonts, colors, textures, and the ability to create custom styles and themes.

- **Animation:** Tools for creating animations for UI elements, including transitions, keyframe animations, and scripting for interactive animations.

- **Input Handling:** A system to manage user input, including mouse, keyboard, and touch events, and routing them to the appropriate widgets.

- **Accessibility:** Features to ensure your UI is accessible to users with disabilities, such as screen readers and keyboard navigation.

- **Internationalization (i18n) and Localization (l10n):** Support for translating UI elements into multiple languages and adapting content for different regions.

- **Data Binding:** A mechanism for binding UI elements to data sources, enabling dynamic updates and synchronization between UI and application data.

- **Custom Widgets:** The ability to create custom widgets and extend the library's functionality as needed.

By including these components and features, RavenUI will offer a focused and efficient solution for creating user interfaces in game development, emphasizing UI design, interactivity, and user experience.


## DocBuilder

DocBuilder is a powerful document builder integrated into our game engine. It is designed to enhance the game development process by providing the following capabilities:

- **Diagrams**: Visualize game architecture, flow, and other aspects.
- **Storyboards**: Plan and visualize game narratives and sequences.
- **Game Bibles**: Create comprehensive documentation of game design, characters, world, mechanics, and more.
- **Export**: Export these documents in common formats for easy sharing and collaboration.

By integrating documentation directly into the game engine, we aim to streamline the game development process and improve team collaboration.

## Other Features

The rest of the features in our game engine will be modeled after those found in Unreal, Unity, and Godot. This includes, but is not limited to, features such as:

- Powerful rendering engine
- Physics engine
- Animation system
- Scripting language support
- Asset management
- And more

We aim to provide a comprehensive toolset for game developers, making it easier to bring their visions to life.





engine lib
C++, X64

level editor
undecidied

Game Code
C++

RAVENUI

what are some modules or components a game engine has? (start it from the tipppy top)
-a main window
---sizable (maximize, minimize, custom) no warping the insides to make everything smaller this has to be a scrolled
---#181818
---test transparency i think a nice 75% could be cool

then in our case

-a plus symbol dead center