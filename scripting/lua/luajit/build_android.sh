#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
host_os=`uname -s | tr "[:upper:]" "[:lower:]"`

SRCDIR=$DIR/LuaJIT
cd "$SRCDIR"

# NOTE: You should setup NDK_ROOT path first
NDK=$NDK_ROOT
NDKABI=24
NDKVER=$NDK/toolchains/arm-linux-androideabi-4.9
NDKP=$NDKVER/prebuilt/${host_os}-x86_64/bin/arm-linux-androideabi-
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm"

# Android/ARM, armeabi-v7a (ARMv7 VFP)
NDKARCH="-march=armv7-a -mfloat-abi=softfp -Wl,--fix-cortex-a8"
DESTDIR=$DIR/android/armeabi-v7a
rm "$DESTDIR"/*.a
make clean
make -j HOST_CC="clang -m32" CROSS=$NDKP TARGET_SYS=Linux TARGET_FLAGS="$NDKF $NDKARCH"

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit.a
fi;

# Android/ARM, arm64-v8a
NDKARCH="-march=armv8-a"
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-arm64"
NDKVER=$NDK/toolchains/aarch64-linux-android-4.9
NDKP=$NDKVER/prebuilt/${host_os}-x86_64/bin/aarch64-linux-android-
DESTDIR=$DIR/android/arm64-v8a
rm "$DESTDIR"/*.a
make clean
make -j HOST_CC="clang -m64" CROSS=$NDKP TARGET_SYS=Linux TARGET_FLAGS="$NDKF $NDKARCH"

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit.a
fi;

# Android/x86, x86 (i686 SSE3)
DESTDIR=$DIR/android/x86
NDKVER=$NDK/toolchains/x86-4.9
NDKP=$NDKVER/prebuilt/${host_os}-x86_64/bin/i686-linux-android-
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-x86"
rm "$DESTDIR"/*.a
make clean
make -j HOST_CC="clang -m32" CROSS=$NDKP TARGET_SYS=Linux TARGET_FLAGS="$NDKF"

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit.a
fi;

make clean
