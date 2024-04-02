# Maintainer: Precise

pkgname=sdrppclean-git
pkgver=v2024.4.2.r0.35df309
pkgrel=1
pkgdesc="The Bloat-free Clean SDR Receiver"
arch=('i686' 'x86_64' 'armv7h' 'aarch64')
source=('git+https://github.com/Mr-Precise/SDRPPClean.git')
license=(GPL3)
depends=('fftw' 'glfw' 'glew' 'libvolk' 'rtaudio')
# Customize it for yourself
#_plugindeps=('airspy' 'airspyhf-git' 'bladerf' 'hackrf' 'libad9361' 'libiio' 'libsdrplay' 'limesuite' 'rtl-sdr' 'soapysdr')
_plugindeps=('rtl-sdr' 'hackrf')

makedepends=('cmake' 'git' 'make' 'pkgconf' "${_plugindeps[@]}")
optdepends=("${_plugindeps[@]}")
provides=('sdrppclean-git' 'sdrpp')
conflicts=('sdrppclean-git' 'sdrpp')
b2sums=('SKIP')

pkgver() {
	cd "${srcdir}/SDRPPClean"
	git describe --long --tags --exclude nightly | sed 's/\([^-]*-\)g/r\1/;s/-/./g'
}

prepare() {
	cd "${srcdir}/SDRPPClean"
	git submodule update --init --recursive
}

build() {
	cmake -B build -S ${srcdir}/SDRPPClean \
		-DOPT_BUILD_SPYSERVER_SOURCE=OFF \
		-DOPT_BUILD_SOAPY_SOURCE=OFF  \
		-DOPT_BUILD_USRP_SOURCE=OFF
	make -C build $MAKEOPTS
}

package() {
	make -C build DESTDIR="$pkgdir/" install
}
