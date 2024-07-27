# Define the Name of the Installer
OutFile "DwindlingGalaxiesInstaller.exe"

# Define the Default Installation Directory
InstallDir "$PROGRAMFILES\DwindlingGalaxies"

# Request Application Privileges for Windows Vista and Later
RequestExecutionLevel highest

# Set the Installer Icon
Icon "Include\Libraries\Images\Logo.ico"

# Define the Default Section for the Installation
Section "MainSection"

  # Output Path for the Installation
  SetOutPath "$INSTDIR"

  # Install the Game Executable
  File "Include\DwindlingGalaxies.exe"

  # Install SFML DLLs
  SetOutPath "$INSTDIR\Libraries\SFML"
  File "Include\Libraries\SFML\bin\sfml-graphics-2.dll"
  File "Include\Libraries\SFML\bin\sfml-window-2.dll"
  File "Include\Libraries\SFML\bin\sfml-system-2.dll"
  File "Include\Libraries\SFML\bin\sfml-audio-2.dll"

  # Install C++ Redistributables
  SetOutPath "$INSTDIR\Libraries\Redist"
  File "Include\Libraries\Redist\VC_redist.x86.exe"
  File "Include\Libraries\Redist\VC_redist.x64.exe"

  # Install Fonts Directory
  SetOutPath "$INSTDIR\Libraries\Fonts"
  File "Include\Libraries\Fonts\Future_Now.ttf"

  # Install Images Directory
  SetOutPath "$INSTDIR\Libraries\Images"
  File "Include\Libraries\Images\Confirm.png"
  File "Include\Libraries\Images\ErrorPopUp.png"
  File "Include\Libraries\Images\GameOver.png"
  File "Include\Libraries\Images\GameOverMenu.png"
  File "Include\Libraries\Images\Helgahst.png"
  File "Include\Libraries\Images\HighScore.png"
  File "Include\Libraries\Images\Laser1.png"
  File "Include\Libraries\Images\Logo1.png"
  File "Include\Libraries\Images\MenuBeginner.png"
  File "Include\Libraries\Images\MenuExpert.png"
  File "Include\Libraries\Images\MenuMedium.png"
  File "Include\Libraries\Images\MondoShawns.png"
  File "Include\Libraries\Images\OptionsAbout.png"
  File "Include\Libraries\Images\OptionsControls.png"
  File "Include\Libraries\Images\OptionsMenu.png"
  File "Include\Libraries\Images\Pause.png"
  File "Include\Libraries\Images\Planet3.png"
  File "Include\Libraries\Images\PopUp.png"
  File "Include\Libraries\Images\PowerUp_01.png"
  File "Include\Libraries\Images\PowerUp_02.png"
  File "Include\Libraries\Images\QuitButton.png"
  File "Include\Libraries\Images\SpaceShip5.png"
  File "Include\Libraries\Images\StartMenu.png"
  File "Include\Libraries\Images\Talz.png"
  File "Include\Libraries\Images\background3.png"
  File "Include\Libraries\Images\main_title.png"

  # Install Scores Directory
  SetOutPath "$INSTDIR\Libraries\Scores"
  File "Include\Libraries\Scores\highScores.txt"

  # Install Sounds Directory
  SetOutPath "$INSTDIR\Libraries\Sounds"
  File "Include\Libraries\Sounds\blaster.wav"
  File "Include\Libraries\Sounds\explosion.wav"
  File "Include\Libraries\Sounds\levelUp.wav"
  File "Include\Libraries\Sounds\powerUp.wav"
  File "Include\Libraries\Sounds\teleport.wav"

  # Install Documentation
  SetOutPath "$INSTDIR\Libraries\Documentation"
  File "Include\README\README.md"
  File "Include\LICENSE\LICENSE.md"

  # Create a shortcut on the Desktop with the custom icon
  CreateShortCut "$DESKTOP\DwindlingGalaxies.lnk" "$INSTDIR\DwindlingGalaxies.exe" "" "$INSTDIR\Logo.ico"
  
  # Write the uninstaller
  WriteUninstaller "$INSTDIR\Uninstaller.exe"

SectionEnd

# Uninstaller section
Section "Uninstall"
  # Remove installed files
  Delete "$INSTDIR\DwindlingGalaxies.exe"
  
  # Remove SFML DLLs
  Delete "$INSTDIR\Libraries\SFML\sfml-graphics-2.dll"
  Delete "$INSTDIR\Libraries\SFML\sfml-window-2.dll"
  Delete "$INSTDIR\Libraries\SFML\sfml-system-2.dll"
  Delete "$INSTDIR\Libraries\SFML\sfml-audio-2.dll"
  
  # Remove C++ Redistributables (they are executables, so they might not be uninstalled here)
  Delete "$INSTDIR\Libraries\Redist\VC_redist.x86.exe"
  Delete "$INSTDIR\Libraries\Redist\VC_redist.x64.exe"

  # Remove Fonts Directory
  Delete "$INSTDIR\Libraries\Fonts\Future_Now.ttf"
  RMDir "$INSTDIR\Libraries\Fonts"

  # Remove Images Directory
  Delete "$INSTDIR\Libraries\Images\Confirm.png"
  Delete "$INSTDIR\Libraries\Images\ErrorPopUp.png"
  Delete "$INSTDIR\Libraries\Images\GameOver.png"
  Delete "$INSTDIR\Libraries\Images\GameOverMenu.png"
  Delete "$INSTDIR\Libraries\Images\Helgahst.png"
  Delete "$INSTDIR\Libraries\Images\HighScore.png"
  Delete "$INSTDIR\Libraries\Images\Laser1.png"
  Delete "$INSTDIR\Libraries\Images\Logo1.png"
  Delete "$INSTDIR\Libraries\Images\MenuBeginner.png"
  Delete "$INSTDIR\Libraries\Images\MenuExpert.png"
  Delete "$INSTDIR\Libraries\Images\MenuMedium.png"
  Delete "$INSTDIR\Libraries\Images\MondoShawns.png"
  Delete "$INSTDIR\Libraries\Images\OptionsAbout.png"
  Delete "$INSTDIR\Libraries\Images\OptionsControls.png"
  Delete "$INSTDIR\Libraries\Images\OptionsMenu.png"
  Delete "$INSTDIR\Libraries\Images\Pause.png"
  Delete "$INSTDIR\Libraries\Images\Planet3.png"
  Delete "$INSTDIR\Libraries\Images\PopUp.png"
  Delete "$INSTDIR\Libraries\Images\PowerUp_01.png"
  Delete "$INSTDIR\Libraries\Images\PowerUp_02.png"
  Delete "$INSTDIR\Libraries\Images\QuitButton.png"
  Delete "$INSTDIR\Libraries\Images\SpaceShip5.png"
  Delete "$INSTDIR\Libraries\Images\StartMenu.png"
  Delete "$INSTDIR\Libraries\Images\Talz.png"
  Delete "$INSTDIR\Libraries\Images\background3.png"
  Delete "$INSTDIR\Libraries\Images\main_title.png"
  RMDir "$INSTDIR\Libraries\Images"

  # Remove Scores Directory
  Delete "$INSTDIR\Libraries\Scores\highScores.txt"
  RMDir "$INSTDIR\Libraries\Scores"

  # Remove Sounds Directory
  Delete "$INSTDIR\Libraries\Sounds\blaster.wav"
  Delete "$INSTDIR\Libraries\Sounds\explosion.wav"
  Delete "$INSTDIR\Libraries\Sounds\levelUp.wav"
  Delete "$INSTDIR\Libraries\Sounds\powerUp.wav"
  Delete "$INSTDIR\Libraries\Sounds\teleport.wav"
  RMDir "$INSTDIR\Libraries\Sounds"

  # Remove Documentation
  Delete "$INSTDIR\Libraries\Documentation\README.md"
  Delete "$INSTDIR\Libraries\Documentation\LICENSE.md"
  RMDir "$INSTDIR\Libraries\Documentation"

  # Remove the installation directory
  RMDir "$INSTDIR\Libraries"
  RMDir "$INSTDIR"

  # Remove shortcut
  Delete "$DESKTOP\DwindlingGalaxies.lnk"
SectionEnd

# Post-installation section to install C++ redistributables
Section "PostInstall"
  # Install C++ redistributables
  ExecWait '"$INSTDIR\Libraries\Redist\VC_redist.x86.exe" /quiet /norestart'
  ExecWait '"$INSTDIR\Libraries\Redist\VC_redist.x64.exe" /quiet /norestart'
SectionEnd