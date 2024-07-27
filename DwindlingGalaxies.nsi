# Define the Name of the Installer
OutFile "DwindlingGalaxiesInstaller.exe"

# Define the Default Installation Directory
InstallDir "$PROGRAMFILES\DwindlingGalaxies"

# Request Application Privileges for Windows Vista and Later
RequestExecutionLevel user

# Define the Default Section for the Installation
Section "MainSection" SEC01

  # Output Path for the Installation
  SetOutPath "$INSTDIR"

  # Install the Game Executable
  File "game"

  # Install SFML DLLs
  File "Libraries\SFML\bin\sfml-graphics-2.dll"
  File "Libraries\SFML\bin\sfml-window-2.dll"
  File "Libraries\SFML\bin\sfml-system-2.dll"
  File "Libraries\SFML\bin\sfml-audio-2.dll"

  # Install C++ Redistributables
  File "path\to\vcredist_x86.exe"
  File "path\to\vcredist_x64.exe"

  # Install Fonts Directory
  SetOutPath "$INSTDIR\Fonts"
  File "Fonts/Future_Now.ttf"

  # Install Images Directory
  SetOutPath "$INSTDIR\Images"
  File "Images/Confirm.png"
  File "Images/ErrorPopUp.png"
  File "Images/GameOver.png"
  File "Images/GameOverMenu.png"
  File "Images/Helgasht.png"
  File "Images/HighScore.png"
  File "Images/Laser1.png"
  File "Images/Logo1.png"
  File "Images/MenuBeginner.png"
  File "Images/MenuExpert.png"
  File "Images/MenuMedium.png"
  File "Images/MondoShawns.png"
  File "Images/OptionsAbout.png"
  File "Images/OptionsControls.png"
  File "Images/OptionsMenu.png"
  File "Images/Pause.png"
  File "Images/Planet3.png"
  File "Images/PopUp.png"
  File "Images/PowerUp_01.png"
  File "Images/PowerUp_02.png"
  File "Images/QuitButton.png"
  File "Images/SpaceShip5.png"
  File "Images/StartMenu.png"
  File "Images/Talz.png"
  File "Images/background3.png"
  File "Images/main_title.png"

  # Install Scores Directory
  SetOutPath "$INSTDIR\Scores"
  File "DwindlingGalaxies/Scores/highScores.txt"

  # Install Sounds Directory
  SetOutPath "$INSTDIR\Sounds"
  File "DwindlingGalaxies/Sounds/blaster.wav"
  File "DwindlingGalaxies/Sounds/explosion.wav"
  File "DwindlingGalaxies/Sounds/levelUp.wav"
  File "DwindlingGalaxies/Sounds/powerUp.wav"
  File "DwindlingGalaxies/Sounds/teleport.wav"

  # Install Documentation
  SetOutPath "$INSTDIR\Documentation"
  File "DwindlingGalaxies/README/README.md"
  File "DwindlingGalaxies/LICENSE/LICENSE.md"
  
  # Create a shortcut on the Desktop
  CreateShortCut "$DESKTOP\DwindlingGalaxies.lnk" "$INSTDIR\game.exe"

SectionEnd

# Uninstaller section
Section "Uninstall"
  # Remove installed files
  Delete "$INSTDIR\game.exe"
  Delete "$INSTDIR\Fonts\Future_Now.ttf"
  Delete "$INSTDIR\Images\Confirm.png"
  Delete "$INSTDIR\Images/ErrorPopUp.png"
  Delete "$INSTDIR\Images/GameOver.png"
  Delete "$INSTDIR\Images/GameOverMenu.png"
  Delete "$INSTDIR\Images/Helgasht.png"
  Delete "$INSTDIR\Images/HighScore.png"
  Delete "$INSTDIR\Images/Laser1.png"
  Delete "$INSTDIR\Images/Logo1.png"
  Delete "$INSTDIR\Images/MenuBeginner.png"
  Delete "$INSTDIR\Images/MenuExpert.png"
  Delete "$INSTDIR\Images/MenuMedium.png"
  Delete "$INSTDIR\Images/MondoShawns.png"
  Delete "$INSTDIR\Images/OptionsAbout.png"
  Delete "$INSTDIR\Images/OptionsControls.png"
  Delete "$INSTDIR\Images/OptionsMenu.png"
  Delete "$INSTDIR\Images/Pause.png"
  Delete "$INSTDIR\Images/Planet3.png"
  Delete "$INSTDIR\Images/PopUp.png"
  Delete "$INSTDIR\Images/PowerUp_01.png"
  Delete "$INSTDIR\Images/PowerUp_02.png"
  Delete "$INSTDIR\Images/QuitButton.png"
  Delete "$INSTDIR\Images/SpaceShip5.png"
  Delete "$INSTDIR\Images/StartMenu.png"
  Delete "$INSTDIR\Images/Talz.png"
  Delete "$INSTDIR\Images/background3.png"
  Delete "$INSTDIR\Images/main_title.png"
  Delete "$INSTDIR\Scores\highScores.txt"
  Delete "$INSTDIR\Sounds\blaster.wav"
  Delete "$INSTDIR\Sounds\explosion.wav"
  Delete "$INSTDIR\Sounds\levelUp.wav"
  Delete "$INSTDIR\Sounds\powerUp.wav"
  Delete "$INSTDIR\Sounds\teleport.wav"
  Delete "$INSTDIR\Documentation\README.md"
  Delete "$INSTDIR\Documentation\LICENSE.md"
  
  # Remove the installation directory
  RMDir "$INSTDIR\Fonts"
  RMDir "$INSTDIR\Images"
  RMDir "$INSTDIR\Scores"
  RMDir "$INSTDIR\Sounds"
  RMDir "$INSTDIR\Documentation"
  RMDir "$INSTDIR"
  
  # Remove shortcuts
  Delete "$DESKTOP\DwindlingGalaxies.lnk"
SectionEnd

# Post-installation section to install C++ redistributables
Section "PostInstall"
  # Install C++ redistributables
  ExecWait '"$INSTDIR\vcredist_x86.exe" /quiet /norestart'
  ExecWait '"$INSTDIR\vcredist_x64.exe" /quiet /norestart'
SectionEnd

