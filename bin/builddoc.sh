#!/bin/sh
BASEDIR=$2
DOCUMENT=$1
TEXINPUTS=${BASEDIR}/template:${TEXINPUTS}
RESOLUTION=600
export TEXINPUTS
cd ${BASEDIR}/out
latex ${BASEDIR}/out/${DOCUMENT}.tex
latex ${BASEDIR}/out/${DOCUMENT}.tex
dvips -D${RESOLUTION} -Z1 ${DOCUMENT}.dvi
ps2pdf -r${RESOLUTION}x${RESOLUTION} ${DOCUMENT}.ps ${DOCUMENT}.pdf
rm -rf $DOCUMENT.aux
rm -rf $DOCUMENT.log