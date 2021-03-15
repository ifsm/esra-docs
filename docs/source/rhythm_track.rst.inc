Rhythm Track
========================================
ESRA includes musical pieces from more than 70 ehtnic groups collected in over
50 countries.  A reasonable system for rhythm similairity estimation has to

The rhythm track implemets a timbre-based theory of musical rhythm :cite:t:`Blass:2013aa` [Blaß2019]). That means,
it does not address the relative temporal distance between note onsets. Instead
it focuses on the actual sounds that are played. To this end, ESRA runs an
:ref:`onset detection <rt-onset>` algorithm, which estimates the temporal
position of note onsets within the piece under consideration. Thereafter,
:ref:`audio features extraction <rt-features>` computes a measure for the
perceived *brightness* of the sounds at each onset. ESRA then estimates the
probabilites to change from one given sound to another. This analysis is
carried out using a :ref:`rt-hmm`.

This approch to rhythm has several advantages:

* Since the model operates only on the actual sound, it avoids any cultural
  bias. Especially, the model does not apply notions of Western rhythm theories
  to other music cultures.

* The numerical representatin of the rhythm is of exactly the same size for
  each piece analyzed in the same track no matter how long the actual piece is.
  This is a crucial feature for further processing stages.

* Musical from literally any music culture a be compoared on a well-defined
  basis.

However, the model does have a some disadvantages, too. These include first,
that temporal information is reduced to a equidistant succession. Additionally,
the model as such can be "hard to read" for humans.  This fact is, however,
mitigated by system structure. Since the models are automatically compared,
users only have to interprete the ouput of the similarity estimation, which is
straight foreward. They, hence, do not have to care too much about details of
the rhythm model.

.. _rt-onset:

Onset detection
----------------------------------------
Onset detection estimates the starting points of note onsets in digital audio
signals. Our approach is based on the standard spectral flux method. An onset
is assumed between two consecutive STFT segements if there is a high per band
difference in spectral energy.

Further details can be found in the documentation of the spectral_flux() method
and the FluxOnsetDetector class from the apollon framework.

.. _rt-features:

Audio feature extraction
----------------------------------------
ESRA descrbies the timbre of an onset in terms of the perceived brightness. The spectral centroid
is know to correlated well with the perception of brightness. 

.. _rt-hmm:

Hidden Markov Model
----------------------------------------
Work in progress.
