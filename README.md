<div align="center">

  <img src="readmeAssets/icon.png" alt="logo" width="200" height="auto" />
  <h1>:musical_note: Melody Tunes :musical_note:</h1>
</div>

<!-- Table of Contents -->

# :notebook_with_decorative_cover: Table of Contents

- [Team Members](#sunglasses-team-members)
- [About the Project](#star2-about-the-project)
  - [Screenshots](#camera-screenshots)
  - [Technology Used](#space_invader-technology-used)
  - [Feature Details](#dart-features)
  - [Color Pallete](#art-color-pallete)
- [Run Project Locally](#toolbox-getting-started)
  - [Prerequisites](#bangbang-prerequisites)
  - [Installation](#gear-installation)
  - [Run Locally](#running-run-locally)
- [Credit/Acknowledgement](#coin-credit-and-acknowledgment)

<!-- People Involved in the project -->

## :sunglasses: Team Members

Our team worked collaboratively to design and build this project from scratch, utilizing **C++** and various libraries for the app interface and functionality.

| ![Abhishek Niraula](readmeAssets/abhishek.png) | ![Sneha Karna](readmeAssets/sneha.png) | ![Prashan Chenta Rai](readmeAssets/prashan.png) | ![Saubhagya Rajbhandari](readmeAssets/saubhagya.png) |
| :--------------------------------------------: | :------------------------------------: | :---------------------------------------------: | :--------------------------------------------------: |
|              **Abhishek Niraula**              |            **Sneha Karna**             |             **Prashan Chenta Rai**              |              **Saubhagya Rajbhandari**               |

<!-- About the Project -->

## :star2: About the Project

**Melody Tunes** is a dynamic and interactive music player application developed in **C++**. This project was created for submission to the **ACES C++ Project** as well as the final project submission for the **Object-Oriented Programming** course in the **First Year, Second Part of Electronics Engineering** at **Purwanchal Campus, IOE**.

<!-- Screenshots -->

### :camera: Screenshots

<div align="center"> 
  <img src="https://placehold.co/600x400?text=Your+Screenshot+here" alt="screenshot" />
</div>

<!-- TechStack -->

### :space_invader: Technology Used

| <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg" width="100px" height="100px"> | <img src="https://www.sfml-dev.org/download/goodies/sfml-icon-small.png" width="100px" height="100px"> | <img src="https://cdn-icons-png.flaticon.com/512/176/176083.png" width="100px" height="100px"> |
| :---------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------: |
|                                                      **C++**                                                      |                                                **SFML**                                                |                                      **TinyFileDialogs**                                       |

- **C++** for core development
- **SFML** for graphical interface and audio handling
- **TinyFileDialogs** for file dialog handling
<!-- Features -->

### :dart: Features

<!-- Color Reference -->

### :art: Color Pallete

- **Primary Color**: `#071952` – This deep blue serves as the base color for the **Melody Tunes** interface, symbolizing professionalism and depth.  
  ![#071952](https://via.placeholder.com/20/071952/000000?text=+) `#071952`

- **Secondary Color**: `#FD3A69` – A vibrant coral red that adds energy and highlights key elements, enhancing the user experience.  
  ![#FD3A69](https://via.placeholder.com/20/FD3A69/000000?text=+) `#FD3A69`

<!-- Getting Started -->

## :toolbox: Getting Started

Follow the instructions below to run the project on your local machine.

<!-- Prerequisites -->

### :bangbang: Prerequisites

Ensure you have the following software installed:

- **C++ compiler**: (e.g., `g++`, `clang`)
- **SFML library**: For graphics and audio handling
- **TinyFileDialogs**: For file browsing functionality
- **Makefile**: If using a `Makefile` to automate build steps

<!-- Installation -->

### :gear: Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your-repo/melody-tunes.git
   cd melody-tunes
   ```

2. **Install SFML**:

   - Download **SFML** from the official site: [SFML Downloads](https://www.sfml-dev.org/download.php).

   - **Linux**:

     Use a package manager like `apt` to install SFML:

     ```bash
     sudo apt-get install libsfml-dev
     ```

   - **Windows**:

     Follow the [SFML Windows Installation Guide](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) for Visual Studio or MinGW setup.

   - **Mac**:

     Install SFML using **Homebrew**:

     ```bash
     brew install sfml
     ```

3. **Install TinyFileDialogs**:

   - Download **TinyFileDialogs** from the official GitHub repository: [TinyFileDialogs GitHub](https://github.com/native-toolkit/tinyfiledialogs).

   - Include the `tinyfiledialogs.h` and `tinyfiledialogs.c` files in your project directory.

   - **Linux**:

     Install TinyFileDialogs using the package manager:

     ```bash
     sudo apt-get install tinyfiledialogs
     ```

### :running: Run Locally

1. **Build the Project**:

   - If you are using a **Makefile**, build the project by running:

     ```bash
     make
     ```

   - Ensure that the **SFML** and **TinyFileDialogs** libraries are properly linked in your **Makefile** or **IDE**.

2. **Run the Project**:

   - After successfully building the project, run the executable:

     ```bash
     ./melody_tunes
     ```

Make sure that both **SFML** and **TinyFileDialogs** libraries are available and linked properly during runtime to avoid errors.
`

### :coin: Credit and Acknowledgment

We would like to express our deepest gratitude to everyone who contributed to the development and success of the **Melody Tunes** project.

- **Team Members**:

  - Abhishek Niraula
  - Sneha Karna
  - Prashan Chenta Rai
  - Saubhagya Rajbhandari

- **Special Thanks**:

  - **Purwanchal Campus, IOE**: For providing us with the opportunity and resources to work on this project as part of our **Object-Oriented Programming** final submission.
  - **ACES (Association of Computer Engineering Students)**: For organizing the **C++ project submission** where this app was also showcased.
  - **Our Faculty**: For their continuous support, guidance, and feedback throughout the project development.

- **Libraries and Tools**:
  - [SFML](https://www.sfml-dev.org): For providing an excellent framework for multimedia, graphics, and audio handling.
  - [TinyFileDialogs](https://github.com/native-toolkit/tinyfiledialogs): For providing an easy-to-use file dialog library that was crucial to our project.

This project wouldn't have been possible without the help and inspiration of all the people mentioned above.
