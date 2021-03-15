Timbre Track
========================================

All timbre features use a Fourier to analyze the sound in adjacent,
non-overlapping frames. The analyzed discrete spectrum :math:`A_i` with
amplitude A and N frequency entries :math:`f_i` is then further processed in
the the four features. Here i is used as the vector bins, which map into
frequency values through the sample frequency s and the analysis window length
l in samples like math:`f_i` = i / (l / s).

Frequency domain features
----------------------------------------

Spectral Centroid
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The spectral centroid C is the center of a spectrum, where the sum of amplitudes of frequencies above and below this center are equal, and is calculated as

.. math::
  C = \frac{\sum_{i=0}^N f_i A_i}{\sum_{i=0}^N A_i} \ .

This corresponds to psychoacoustic brightness perception.


Spectral Spread
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Spectral Skewness
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Spectral Kurtosis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Spectral Flux
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Time domain features
----------------------------------------

Fractal correlation dimension
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The fractal correlation dimensions measures chaoticity. Chaoticity is defined
the the amount of harmonic overtone spectra plus large amplitude fluctuations.
So a single guitar tone in its steady-state has a fractal correlation dimension
of one. A piano chord with three keys pressed has a fractal dimension of three.
Each inharmonic sinusoidal added another dimension. White noise therefore has a
dimension of infinity.

To calculate a fractal correlation dimension, a time series x(t) of recorded
sound with n sample points is embedded in a pseudo phase-plot like

.. math::
  X(t) = \{x(t),x(t+\delta), x(t+ 2\delta), ..., x(t+d \delta)\}\ .

Starting from X(t) we then calculate the 'area' or 'volume' C(r) like

.. math::
  C(r) = \frac{1}{N^2} \sum_{i \neq j} H(r-|\mathbf{X}_i -\mathbf{X}_j|) \ .

Here, H(x) is the Heavyside function with

.. math::
  H(x) = \left\{%
  \begin{array}{ll}
    0, & \hbox{for x} \leq 0 \\
    1, & \hbox{for x > 0} \\
  \end{array}%
  \right.

which counts the amount of points within the radius r. C(r) is a probability, as we normalize with respect to all :math:`N^2` possible combinations.

Then the correlation dimension is defined as

.. math::
  D_C = \lim_{r \rightarrow 0} \frac{\ln C(r)}{\ln r} \ ,

which is derived from the idea of the definition of the dimension (Bader2013). The exponent is the dimension which is the slope of a log-log plot. So practically we need to take the middle of the distribution and look for a constant slope in the log-log plot. This slope is the correlation dimension.

This is a very powerful tool as it has certain properties:

1. If only one harmonic overtone spectrum is in the sound, DC = 1 no matter how many overtones are present.
2. Each additional harmonic overtone spectrum raises DC to the next integer.
3. If only one inharmonic sinusodial is added, DC raises to the next integer making it suitable for detection of additional single inharmonic components too.
4. Large amplitude fluctuations lead to a raise of DC.
5. As the absolute amplitude is normalized, DC does not depend upon amplitude.
6. If a component is below a certain amplitude threshold it is no longer considered by the algorithm.

The fractal correlation dimension raises with initial transients, as they contain chaoticity. It is also a good measure of event density in a musical piece.

7. Correlogram

The correlogram is the opposite to the fractal dimensin. There the chaoticity
is calculated, a correlogram calculates the harmonicity. While with very
complex sounds the fractal dimension is at a maximum, with these sounds the
correlogram becomes nearly zero.

It is calculated for a time series y(t)  for time points t and frequency f = i
/ S with sample frequency S and running sample delay i like

.. math::
  C(t, i) = \frac{A_{t,i}^M}{\sqrt{B_t^M C_{t,i}^M}} \ .

Here :math:`A_{t,i}^M` is the autocorrelation sum

.. math::
  A_{t,i}^M = \sum_{j=0}^M y(t+j) y(t+i+j)

at point t for sample delay i, corresponding to a frequency, over
an autocorrelation length M. It is normalized by

.. math::
  B_t^M = \sum_{j=0}^M y(t+j)^2 \ ,

as the squared length of the time series vector over M starting at t, and by

.. math::
  C_{t,i}^M = \sum_{j=0}^M y(t+i+j)^2 \ ,

as the squared sum of the time series vector over M starting from t + i. So after inserting A, B, and C we have

.. math::
  C(t, i) = \frac{\sum_{j=0}^M y(t+j) y(t+i+j)}{\sqrt{\sum_{j=0}^M y(t+j)^2 \sum_{j=0}^M y(t+i+j)^2}} \ .

The correlogram is equivalent to an autocorrelation of an autocorrelation. The
first autocorrelation detects periodicities within the sound. These periodicity
series are again used as the input of another autocorrelation. So by applying
this convolution integral twice, we detect not single frequencies but
periodicities of frequencies, harmonic series.


Models of perceptional qualities
----------------------------------------

Loudness
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Although several algorithms of sound loudness have been proposed by :cite:t:`Fastl:2007aa`,
for music still no satisfying results have been obtained :cite:p:`Ruschkowski:2013aa`. Most
loudness algorithms aim for industrial noise and it appears that musical
content considerably contributes to perceived loudness. Also loudness is found
to statistically significantly differ between male and female subjects due to
the different constructions of the outer ears between the sexes. Therefore a
very simple estimation of loudness is used, and further investigations in the
subject are needed. The algorithm used is

.. math::
 L = 20 \log_{10} \frac{1}{N}\sqrt{\sum_{i=0}^N \frac{A_i^2}{A_{ref}^2}} \ .

This corresponds to the definition of decibel, using a rough logarithm-of-ten
compression according to perception, and a multiplication with 20 to arrive at
120 dB for a sound pressure level of about 1 Pa. Of course the digital audio
data are not physical sound pressure levels (SPL), still the algorithm is used
to obtain dB-values most readers are used to. As all psychoacoustic parameters
are normalized before inputting them into the SOM, the absolute value is not
relevant.


Roughness
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Roughness calculations have been suggested in several ways (for a review see
:cite:p:`Schneider:2009aa`, :cite:p:`Bader:2013aa`). Basically two algorithms exist, calculating
beating of two sinusoidals close to each other (Helmholtz ({Helmholtz1863),
Helmholtz/Bader (Schneider2009), Sethares (Sethares1993), or integrating energy
in critical bands on the cochlear (Fastl (Zwicker1999), Sothek (Sothek1994).
The former has been found to work very well with musical sounds, the latter
with industrial noise. 

In the paper a modified Helmholt/Bader algorithm is used. Like Helmholtz it
assumes a maximum roughness of two sinusoidals at 33 Hz frequency difference.
As Helmholtz did not give a mathematical formula how he did calculate
roughness, according to his verbal descriptions a curve of the amount of
roughness :math:`R_n` is assumed between two frequencies with distance :math:`df_n` which
have amplitudes :math:`A_1` and :math:`A_2` like

.. math::
  R_n = A_1 A_2 \frac{|df_n|}{f_r e^{-1}} e^{- |df_n|/f_r} \ .

with a maximum roughness at :math:`f_r=33` Hz. The roughness :math:`R` is then calculated
as the sum of all possible sinusoidal combinatins like

.. math::
  R = \sum_{i=1}^N R_i \ .

The only difference between the algorithm used in apollon and that described in
(Schneider2009) is the precision with which the frequencies are calculated. To
arrive at very precise values in (Schneider2009) a wavelet analysis is
performed, allowing for an arbitrary precision of frequency estimation. As this
is very expensive in terms of computational time, in the present study the
above described Fourier analysis precision is used. In ({Schneider2009} the
research aim was to tell the perceptual differences between tuning systems like
Pure Tone, Werkmeister, Kirnberger, etc. in a Baroque piece of J.S. Bach which
succeeded. The present analysis is not aiming for such subtle differences, but
for the overall estimation of roughness.


Sharpness
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Perceptual sharpness is related to the work of Bismarck (Bismarck1974) and
followers (Aures1985b, Fastl2007). It corresponds to small frequency-band
energy. According to (Fastl2007) it is measured in acum, where 1 acum is a
small-band noise within one critical band around 1 kHz at 60 dB loudness level.

Sharpness increases with frequency in a nonlinear way. If a small-band noise
increases its center frequency from about 200 Hz to 3 kHz, sharpness increases
slightly, but above 3 kHz strongly, according to perception that very high
small-band sounds have strong sharpness. Still sharpness is mostly independent
of overall loudness, spectral centroid, or roughness, and therefore qualifies
as a parameter on its own.

To calculate sharpness the spectrum A is integrated with respect to 24 critical
or Bark bands, as we are considering small-band noise. With loudness :math:`L_B` at
each Bark band :math:`B`, sharpness is

.. math::
  S = 0.11 \frac{\sum_{B=0}^{24 Bark} L_B g_B B}{\sum_{B=0}^{24 Bark} L_B} \,,  

where a weighting function $g_B$ is used strengthening sharpness above 3 kHz
like({Peeters2004}

.. math::
  g_B = \left\{\begin{array}{ll} 1 \text{ if} B < 15 \\ 0.066 e^{0.171 B} \text{ if} z \geq 15 \end{array} \right.


Example
----------------------------------------
Below the an example result of two sets of Hip Hop musical pieces. A SOM was trained with a certain amount of features, able to cluster Chinese (red) and Western (violet) Hip Hop pieces.

.. figure:: fig/TimbreTrack_SOM_Example_HipHop.png
   :scale: 100 %
   :alt: TimbreTrack_SOM_Example_HipHop

