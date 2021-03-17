Timbre Track
========================================
The TimbreTrack combines a set of audio features to model the timbral content of piece of music.
These features are computed on short, consecutive portions of the input signal.

Frequency domain features
----------------------------------------
Frequency domain features are computed from a spectrogram. A spectrogram
displays the distribution of energy within the audible frequency bands of
consecutive, short portions of the input signal. ESRA computes its spectrograms using
the Discrete Fourier Transform.

The shape of each spectral distributions is related to how humans perceive the timbre
of the related portion of a musical piece. Typically, the first four moments of a distribution
are utilized to describe its shape.

Spectral Centroid
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The first moment of a spectral energy distribution is the spectral centroid
frequency.  It is a measure of central tendency. It marks the frequency that is
considered as the center of a spectrum. It may be computed as the weighted
arithetic mean of a frequency spectrum. 

Several studies could confirm that the spectral centroid correlates strongly
with the human auditory perception of *brightness*. Moreover, brightness is the
most salient dimension of timbre perception.

Detailed information can be found in apollon.signal.features.spectral_centroid.

.. !! include figure for illustration

Spectral Spread
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Spectral Spread is the second moment of a spectral distribution and refers to
its variance.  It is a measure of how much frequencies deviate from the
spectral centroid frequency.

Unlike Spectral Centroid, Spectral Spread does not map immediately to a
perceptional quality.

Detailed information can be found in apollon.signal.features.spectral_spread.

.. !! include figure for illustration

Spectral Skewness
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Spectral skewness is the third spectral moment. A skewness of 0 means that the
distribution is perfectly symmetric. Negative values indicate a bias towards
high frequency. Conversely, positive values indicate a displacement to low
frequencies.

Detailed information can be found in apollon.signal.features.spectral_skewness.

.. !! include figure for illustration

Spectral Kurtosis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Spectral kurtosis is the fourth spectral moment. It is a measure for the shape
of the tails of a distribution.

Detailed information can be found in apollon.signal.features.spectral_kurtosis.

.. !! include figure for illustration

Spectral Flux
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Spectral flux is the change in amplitude per frequency bin over time. It is
particularly useful for timbre.

Detailed information can be found in apollon.signal.features.spectral_flux.

.. !! include figure for illustration


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

which is derived from the idea of the definition of the dimension (Bader2013).
The exponent is the dimension which is the slope of a log-log plot. So
practically we need to take the middle of the distribution and look for a
constant slope in the log-log plot. This slope is the correlation dimension.

This is a very powerful tool as it has certain properties:

1. If only one harmonic overtone spectrum is in the sound, DC = 1 no matter how many overtones are present.
2. Each additional harmonic overtone spectrum raises DC to the next integer.
3. If only one inharmonic sinusodial is added, DC raises to the next integer making it suitable for detection of additional single inharmonic components too.
4. Large amplitude fluctuations lead to a raise of DC.
5. As the absolute amplitude is normalized, DC does not depend upon amplitude.
6. If a component is below a certain amplitude threshold it is no longer considered by the algorithm.

The fractal correlation dimension raises with initial transients, as they contain chaoticity. It is also a good measure of event density in a musical piece.


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
:cite:p:`Schneider:2009aa` and :cite:p:`Bader:2013aa`). Basically two algorithms
exist, calculating beating of two sinusoidals close to each other
:cite:p:`Helmholtz:1863aa, Schneider:2009aa, Sethares:1993aa` or integrating
energy in critical bands on the cochlear :cite:p:`Fastl:2007aa, Sottek:1994aa`.
The former has been found to work very well with musical sounds, the latter
with industrial noise. 

In the paper a modified Helmholt/Bader algorithm is used. Like Helmholtz it
assumes a maximum roughness of two sinusoidals at 33 Hz frequency difference.
As Helmholtz did not give a mathematical formula how he did calculate
roughness, according to his verbal descriptions a curve of the amount of
roughness :math:`R_n` is assumed between two frequencies with distance :math:`df_n` which
have amplitudes :math:`A_1` and :math:`A_2` like

.. math::
  R_n = A_1 A_2 \frac{|df_n|}{f_r e^{-1}} e^{- |df_n|/f_r} \,.

with a maximum roughness at :math:`f_r=33` Hz. The roughness :math:`R` is then calculated
as the sum of all possible sinusoidal combinatins like

.. math::
  R = \sum_{i=1}^N R_i \,.

The goal of :cite:t:`Schneider:2009aa` was to model the perceptual differences of tuning systems like
Pure Tone, Werkmeister, Kirnberger, etc. in a Baroque piece of J. S. Bach. This task required high temporal and spatial resolution in 
the frequecy domain. The authors, therefore, utilized a `Discrete Wavelet Transform`_ (DWT). The roughness analysis in ESRA does not aim for such subtle differences, but
for an overall estimation. Moreover, ESRA has to accomodate resource restrictions. To this end, the DWT was replaced by the Discrete Fourier Transform.

.. _Discrete Wavelet Transform: https://en.wikipedia.org/wiki/Discrete_wavelet_transform

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

