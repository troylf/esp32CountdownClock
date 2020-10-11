# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.cpp"
	"spiInit.c" 
	"MatrixDisplay.cpp"
	"MatrixChars.cpp"
	"Countdown.cpp"
	"Wifi.c"
	)
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
