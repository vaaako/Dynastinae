#!/bin/bash

declare -A os_pack;
os_pack[/etc/redhat-release]=yum
os_pack[/etc/arch-release]=pacman
os_pack[/etc/gentoo-release]=emerge
os_pack[/etc/SuSE-release]=zypp
os_pack[/etc/debian_version]=apt-get

FOUND=false
PACK="" # Package manager
BOLD="\033[1m"
NC="\033[0m"

for f in ${!os_pack[@]}; do
	if [ -f $f ]; then
		PACK="${os_pack[$f]}"
		FOUND=true
	fi
done

if [[ ! $FOUND ]]; then
	echo "Package manager not identified"
	exit
fi

case $PACK in
	# Fedora can have yum or dnf
	"yum")
		echo -e "~> Fedora identified!\n"
		if [ -f /bin/dnf ]; then
			sudo dnf install glew sdl2 sdl2_image sdl2_mixer sdl2_ttf glm-devel
			echo -e "\n\n~> if $bold glm-devel$nc didn't download correctly, try downloading $bold glm$nc"

		elif [ -f /bin/yum ]; then
			sudo yum install glm-devel glew-devel sdl2-devel sdl2_image-devel sdl2_mixer-devel sdl2_ttf-devel

		else
			echo -e "Libs not found on your package manager! Please install manually \nRequired libs: glm glew sdl2 sdl2_image sdl2_mixer sdl2_ttf"
		fi
		;;

	"pacman")
		echo -e "~> Arch Linux identified!\n"
		sudo pacman -S glm glew sdl2 sdl2_image sdl2_mixer sdl2_ttf
		;;

	"emerge")
		echo -e "~> Gentoo identified!\n"
		sudo emerge media-libs/glm media-libs/glew media-libs/libsdl2 media-libs/sdl2-image media-libs/sdl2-mixer media-libs/sdl2-ttf
		;;

	"zypp")
		echo -e "~> OpenSuSe identified!\n"
		sudo zypper install glew sdl2 sdl2_image sdl2_mixer sdl2_ttf
		echo -e "\n\n$BOLD~> glm not found in this package manager!$NC"
		;;

	"apt-get")
		echo -e "~> Ubuntu/Debian identified!\n"
		sudo apt-get install libglm-dev libglew-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
		;;

	*)
		echo -e "Libs not found on your package manager! Please install manually \nRequired libs: glm glew sdl2 sdl2_image sdl2_mixer sdl2_ttf"
		exit
		;;
esac
