an02022 change log
==================

1.2.0
-----

  * FIXED:     Description of frequencies and dividers
  * FIXED:     Bit 27 must be set not cleared to enable the Secondary PLL (#13)
  * FIXED:     The hex values to set the Secondary PLL
  * FIXED:     XN oscillator frequency set to 24 MHz to match XK-EVK-XU316 (#21)

1.1.0
-----

  * ADDED:     Clarification of Secondary PLL differences
  * ADDED:     Missing constraints regarding PLL configuration
  * ADDED:     Clarification on F, R, OD values vs register values
  * ADDED:     Further emphasis on valid range for on F, R, OD values
  * ADDED:     Section with guidance on keeping PLL output jitter low
  * CHANGED:   Various minor documentation improvements
  * FIXED:     PLL adaption period corrected from 50 to 500 input clocks
  * FIXED:     Updated diagram in Fig 1 to represent a valid configuration

1.0.0
-----

  * Initial public release

