:orphan:

Analog Model
============

Goals
-----

.. so

    this showcase describes the available analog models, their degrees of freedom, limitations
    advantages, and the typical use cases

    benefit/advantage

    when to use which one

    -what are analog models

    In INET, radio signal analog models

    The analog representation of radio signals

    so

    - analog signal representation models how radio signals are
    - signal analog models model radio signals are they are transmitted, received and propagate
    - how the signals are represented
    - there are multiple models, with different complexity, depending on which is needed

    - tradeoff between accuracy and performance

    Radio signal analog models model signals as they are transmitted, received and propagate in the wireless medium.

    Radio signal analog models represent signals as they are transmitted, received and propagate in the wireless medium. Models of different complexity are available, suitable for different purposes.
    Ranging from less accurate models when simulating the details of radio signals is not important, to very accurate but slower models for accurate signal simulation.

    Some example...

    the unit disk just has a range (two ranges)
    the scalar has frequency data but nothing else
    the dimensional models spectrums accurately

**V1** In INET, radio signal analog models represent signals as they are transmitted, received and propagate in the wireless medium. Models of different complexity are available, suitable for different purposes.

.. The analog model implements how signals as a physical phenomena are represented as they are transmitted, received and propagate in the wireless medium. It specifies at what detail level they are represented, what features of them are modeled.

**V2** In INET, analog models implement how signals as physical phenomena are represented as they are transmitted, received and propagate? through the wireless medium. Analog models of different complexity are available, differing from each other in detail level, and modeled PHY-layer features.

.. This showcase describes the avaialbe analog signal representation models, their advantages and drawbacks, and typical use cases. There are three example simulations for typical use cases. **TODO** emphasize example

This showcase describes the avaialbe analog signal representation models, their advantages and drawbacks, and contains three example simulations for typical use cases.

.. Through three example simulations.

   - there are examples for typical use cases

| INET version: ``4.2``
| Source files location: `inet/showcases/wireless/analogmodel <https://github.com/inet-framework/inet-showcases/tree/master/wireless/analogmodel>`__

About Analog Models
-------------------

more details about analog models, performance/accuracy
what kinds are available
its part of the radio medium module

    so

    the analog model

    - it implements the analog signal representation, i.e. how signals as a physical phenomena are represented/at what detail level they are represented/what features of them are represented/modeled.
    - this is a simple module, a submodule of the radio medium module
    - several types exist, ranging from simple to complex, suitable for different purposes
    - when the details are not important, a simpler model is sufficient
    - such as the unit disk is sufficient for testing routing protocols, because it just has a communication range, and that level of abstration is enough for testing routing protocols
    - but when its important that reception depends on distance/power level and snir, the scalar model is sufficient. there is just one wifi channel, the interesting part is the snir
    - then the emphasis might be on multiple wifi channels and interference. for that the dimensional analog model is needed

The analog signal representation is implemented as a submodule of the radio medium module.
INET contains the following analog model types, presented in the order of increasing complexity:

- **Unit disk**: Simple model featuring communication, interference and detection ranges as parameters. Suitable for simulations where the emphasis is not on the details of radio transmissions, but something else, e.g. testing routing protocols.

- **Unit disk**: Simple model featuring communication, interference and detection ranges as parameters. Reception in communication range is always successful, and outside of it always unsuccessful. Signals can be detected in the interference range, which might cause network nodes to defer from transmitting. Suitable for simulations where the emphasis is not on the details of radio transmissions, but something else, e.g. testing routing protocols.

.. - **Scalar**: Signal power is represented by a scalar value. Transmissions have a center frequency and bandwidth; **TODO** attentuation due to distance or other stuff Signal interfere when their center frequency and bandwidth is exactly the same (and the signal power is high enough TODO). When there is no overlap in the frequency spectrum, they don't interfere. Overlapping signals can't be simulated with this model, it throws and error. **TODO** suitable for what

- **Scalar**: Signal power is represented with a scalar value. Transmissions have a center frequency and bandwidth, but modeled as flat signals in frequency and time. Attenuation is simulated, and a SNIR value for reception can be calculated and used by error models to calculate reception probability. Signals can interfere only when their center frequency and bandwidth is exactly the same. Suitable for simulations where wireless channel, attenuation, SNIR, and error modeling is required/ but the emphasis is not on the details of the wireless PHY layer.

.. Transmissions are modeled as flat signals in frequency and time;

.. Signals with overlapping spectrums can't be simulated with this model.

.. **TODO** suitable for what

- **Dimensional**: Signal power is represented as a multidimensional function of frequency and time; arbitrary signal shapes can be defined in time and the frequency spectrum. Simulates attenuation and SNIR. Suitable for simulating interference of signals with partially overlapping spectrums, and cross-technology interference (**TODO** see also Coexistence).

.. In addition to simulating attenuation and SNIR

.. **TODO** suitable for accurate interference and CTI simulation

.. - **Dimensional**: Signal power is represented as a multidimensional function of frequency and time; arbitrary signal shapes can be defined in time and the frequency spectrum. Interference is modeled accurately. Suitable for simulating cross-technology interference (**TODO** see also Coexistence).

More complex models are more accurate but require more computing performance.
INET contains a version of radio and radio medium module for each type and technology, e.g. :ned:`Ieee80211UnitDiskRadio`/:ned:`UnitDiskRadioMedium`, :ned:`ApskScalarRadio`/:ned:`ApskScalarRadioMedium`,
:ned:`Ieee802154NarrowbandDimensionalRadio`/:ned:`Ieee802154NarrowbandDimensionalRadioMedium`, etc.
**TODO** these models use the appropriate analog signal representation (i.e. the receiver, the transmitter, and the radio medium)

INET contains a version of radio module for each analog model type and technology, e.g. for 802.11, there is :ned:`Ieee80211UnitDiskRadio`, :ned:`Ieee80211ScalarRadio` and :ned:`Ieee80211DimensionalRadio`. Similarly, other technologies (e.g. 802.15.4, Apsk radio) have the approrpirate versions.

These modules usually have a corresponding radio medium module as well, e.g. :ned:`Ieee80211ScalarRadioMedium`, :ned:`Ieee802154NarrowbandDimensionalRadioMedium`, etc.

The corresponding radio and radio medium modules should be used together, but they can just be used with :ned:`RadioMedium` by setting the analog model type to the appropriate one in the radio medium module. The different radio medium module types don't have associated C++ classes, just extend RadioMedium with parameter settings suitable for the given technology.**TODO**

The unit disk model is very simple and it doesn't have technology specific radio medium modules; all unit disk radios can be used with the generic UnitDiskRadioMedium (which is just RadioMedium with the analog model type set to unit disk)

**TODO** these models use the appropriate analog signal representation (i.e. the receiver, the transmitter, and the radio medium)

INET contains versions of technologies with the different analog model types, e.g. e.g. :ned:`Ieee80211UnitDiskRadio`/:ned:`UnitDiskRadioMedium`, :ned:`ApskScalarRadio`/:ned:`ApskScalarRadioMedium`,
:ned:`Ieee802154NarrowbandDimensionalRadio`/:ned:`Ieee802154NarrowbandDimensionalRadioMedium`, etc.

so

- there are technologies in INET such as Wifi, 802.15.4, apsk radio
- there are versions of these with different analog models: Ieee80211UnitDiskRadio, Ieee80211ScalarRadio, Ieee80211DimensionalRadio
- these have corresponding radio medium modules: UnitDiskRadioMedium, Ieee80211ScalarRadioMedium, Ieee80211DimensionalRadioMedium

..     so

    - signal power is represented as a function of frequency and time
    - arbitrary signal shape can be defined in frequency and time
    - its a multi dimensional function
    - attenuation, signal spectrum and interference is modeled accurately
    - can model CTI -> can the scalar model cti ?

    so

    there are types as in unit disk, scalar and dimensional
    and also types as in ieee80211, apsk, ieee802154 etc

    There are several

Unit Disk Example: Testing routing protocols
--------------------------------------------

    - this example is about the unit disk
    - why is this good for routing?
    - what are the drawbacks/benefits
    - what are the parameters and the available models
    - the config/network
    - the results (show the ranges, something about the transmissions in the inspector

..  so the parameters are set in the transmitter and the receiver

  there are some degrees of freedom; the ranges, and some features of protocols are configurable, such as headerlength, bitrate, preambleduration. These are configured in the transmitter.
  The receiver has the ignoreInterference parameter.

  This example simulation demonstrates the unit disk analog model. The model is the simplest available in INET; it only models a communication range and an interference range. Tranmissions are always successfully received in the communication range, and never outside of it. Transmissions in the interference range can cause network nodes to back off from transmitting **TODO**. Also can set preamble duration, headerlength, and bitrate (used for calculating transmission duration). Set these in the transmitter. Set the ignoreInterference in the receiver.

The unit disk analog model is the simplest available in INET. It models three ranges, configurable with parameters:

..  of unit disk transmitters

- **Communication range**: tranmissions are always successful within this range (unless ruined by another interfering signal)
- **Interference range**: transmissions can't be received successfully in this range, but they can ruin other receptions
- **Detection range**: transmission can't interfere with other transmissions in this range, but they can cause network nodes detecting them to defer from transmitting (when using a suitable MAC module, such as :ned:`CsmaCaMac` or :ned:`Ieee80211Mac`)

These ranges can be set in the unit disk transmitters (:par:`communicationRange`, :par:`interferenceRange`, :par:`detectionRange` parameters).
Furthermore, the unit disk transmitters model some protocol features, configurable by parameters, such as :par:`headerLength`, :par:`preambleDuration`, and :par:`bitrate`; the bitrate is used to calculate transmission duration.

.. **TODO**: the actual parameters

The unit disk receiver's :par:`ignoreInterference` parameter configures whether interfering signals ruin receptions (``false`` by default).

.. **TODO**

  - why is it good? for what purpose?
  - what modules are available? and how to use it
  - ideally, the ranges should be incrementally larger

.. The unit disk analog model is suitable for wireless simulations in which the details of the physical layer is not important, such as testing routing protocols.
   The unit disk analog model is used by the :ned:`UnitDiskRadio` module; the module contains a :ned:`UnitDiskTransmitter` and a :ned:`UnitDiskReceiver` module.
   :ned:`UnitDiskRadio` can be used with :ned:`UnitDiskRadioMedium`.
   Also, there is a unit disk version of Wifi: the :ned:`Ieee80211UnitDiskRadio` module contains a :ned:`Ieee80211UnitDiskTransmitter` and a :ned:`Ieee80211UnitDiskReceiver`.
   (to be used with :ned:`UnitDiskRadioMedium`).

The unit disk analog model is suitable for wireless simulations in which the details of the physical layer is not important, such as testing routing protocols. The following modules use the unit disk analog model:

- :ned:`UnitDiskRadioMedium`: the only radio medium using the unit disk analog model; to be used with all unit disk radio types
- :ned:`UnitDiskRadio`: generic radio using the unit disk analog model; contains :ned:`UnitDiskTransmitter` and :ned:`UnitDiskReceiver`
- :ned:`Ieee80211UnitDiskRadio`: unit disk version of Wifi; contains :ned:`Ieee80211UnitDiskTransmitter` and :ned:`Ieee80211UnitDiskReceiver`

**TODO** mention AckingInterface ?

..  so

  - in INET, the unit disk analog model can be used with several wireless protocols/technnologies
  - there is a Wifi version (Ieee80211UnitDiskRadio which contains Ieee80211UnitDiskTransmitter)
  - and there is the UnitDiskRadio with UnitDiskTransmitter and UnitDiskReceiver
  - and there is the UnitDiskRadioMedium. This is the only unit disk radio medium type
  - so the macs...is this showcase about that? should they be mentioned? if relevant
  - AckingWirelessInterface -> unitdiskradio+ackingmac -> this has the unit disk radio

  - so there is the UnitDiskRadioMedium -> to be used with any unit disk analog models
  - there is the UnitDiskRadio -> UnitDiskTransmitter, UnitDiskReceiver
  - there is the Ieee80211UnitDiskRadio -> Ieee80211UnitDiskTransmitter, Ieee80211UnitDiskReceiver
  - AckingInterface -> UnitDiskRadio -> might not be needed

  - so basically UnitDiskRadioMedium + UnitDiskRadio (which has the UDtx, UDrx)
    use it with a mac
  - and there is the Wifi version

- its simple and runs fast; suitable for scenarios where the details of tranmissisons don't matter/the emphasis is not on that, for example, routing

.. - there are actually, there are radios, which contain the transmitters and receivers
   and there is the radio medium...need to use compatible...some examples
   and there are some MAC's which can be used...not all features of the unit disk can be used with all MACs...the ackingmac doesnt do defer...need csmaca for that
   there is apsk and wifi...there are interfaces...

.. It has three ranges configurable by parameters:

  - Communication range: tranmissions are always successful (unless ruined by an interfering signal)
  - Interference range: transmissions can't be received successfully, but they can ruin other receptions
  - Detection range: transmission can't interfere with other transmissions, but can cause network nodes detecting them to defer from transmitting (when using a suitable MAC module, such as CsmaCaMac or Ieee80211Mac)

**TODO** need to use the appropriate radio medium, and radio modules (which have the correct transmitter and receiver types) -> not here

We'll demonstrate the unit disk analog model in an example scenario featuring mobile adhoc hosts, which use the AODV protocol to maintain routes:

.. .. figure:: media/unitdisknetwork.png
      :width: 100%
      :align: center

.. figure:: media/unitdisknetwork2.png
   :width: 100%
   :align: center

In the simulation, ``source`` sends ping requests to ``destination``, and ``destination`` sends back ping replies. The source and the destination host are stationary, the other hosts move around the scene in random directions. The hosts use :ned:`Ieee80211UnitDiskRadio`, and the communication ranges are displayed as blue circles. All hosts use the Ad hoc On-Demand Distance Vector Routing (AODV) protocol to maintain routes as the topology changes, so that they are able to relay the ping messages between the source and the destination hosts.

.. **TODO** why in this scenario unit disk is the right choice ?

.. **V1** In this scenario, the emphasis is on the connectivity of the source and destination hosts,

This scenario examines the connectivity of the source and destination hosts,
i.e. how the moving intermediate hosts can build temporary routes and relay the ping messages. In this context, the communication ranges of the hosts is an adequate abstraction of the physical layer communication, thus the unit disk analog model is suitable for this purpose.

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :start-at: Config Routing3
   :end-at: displayCommunicationRanges
   :language: ini

.. - sometimes there is connectivity between the two hosts
   - sometimes there isnt

Here is a video of the simulation running (successful ping message sends between the source and destination hosts are indicated with colored arrows; routes to destination are indicated with black arrows):

.. TODO

.. .. video:: media/Aodv5_s.mp4
   :width: 80%

.. video:: media/unitdisk1.mp4
   :width: 80%

.. video:: media/unitdisk2.mp4
   :width: 80%

.. **TODO** communication range

.. TODO display just the routes

The source and destination hosts are connected intermittently. If the intermediate nodes move out of range before the routes can be built then there is no connectivity. This can happen if the nodes move too fast, as route formation takes time due to the AODV protocol overhead.

.. - this can be used to run simulations to figure out how fast the nodes can move so that connectivity can be maintained
   - as the AODV protocol has overhead
   - if the intermediate nodes move out of range before the routes can be built then there would be no connectivity

   - this should be in the intro part of this section ?

**TODO** what are the drawbacks/benefits ?

Scalar Example: SNIR and Packet Error Rate vs Distance
------------------------------------------------------

**TODO** Throughput/SNIR vs Distance

  - this example is about the scalar
  - **why is t his good for this purpose? cos we need the attenuation/the reception needs to depend on the power levels**
  - **drawbacks/benefits/degrees of freedom**
  - parameters, available models
  - config/network
  - results (show the BER/PER/number of packets)(should a study?)

.. **V1** The scalar analog model represents transmissions with a scalar power value, a center frequency and a bandwidth, and might include other protocol features as well **TODO**. **TODO** there is also modulation.
   The scalar representation can model attenuation, and is able to compute a signal-to-noise-interference radio (SNIR). The SNIR is used by error models to calculate bit-error-rate and packet-error-rate. **TODO** this is a benefit...a limitation is that it cant simulate partially overlapping spectrums or realistic signal shapes both in frequency and time. it just simulates a boxcar signal in frequency and time. These can either completely overlap (interference) or not at all (no interference).

.. **TODO** types

.. --------

   about the scalar analog model

   interference

   types

   other protocol features

   --------

.. scalar model

  main features are power, center frequency and bandwidth -> it models attenuation -> it uses all these to calculate a SNIR -> which is used by the error model to calculate BER and PER
  other features are preambleDuration, bitrate, etc. Sometimes these are set in the transmitter (ApskRadio) but other technologies these are set automatically (Wifi)
  you just specify a channelNumber and an opMode
  It has a boxcar signal shape in frequency and time
  This has high performance and its good for interference if the spectrums are the same (same Wifi channel)
  And if they dont overlap at all then the transmissions are independent

  There are scalar versions of the following wireless technologies in INET: IEEE 802.11, IEEE 802.15.4, and Apsk Radio.
  Each have a radio module and a corresponding radio medium module.

.. The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth. It models attenuation, so that the signal power decreases with distance from the transmitter.

.. **V2.1** The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth; it models attenuation. It uses these to calculate a signal-to-noise-interference ratio (SNIR) at reception. The SNIR can be used by error models to calculate bit error rate and packet error rate of receptions.

**V2** The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth. The scalar representation models attenuation, and is able to calculate a signal-to-noise-interference radio (SNIR) at reception. The SNIR can be used by error models to calculate bit error rate and packet error rate of receptions.

.. Signals are represented with a boxcar shape in frequency and time. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

.. INET contains scalar versions of wireless technologies, such as IEEE 802.11 and 802.15.4; it also contains the scalar version of ApskRadio, which is a generic radio featuring different modulations such as BPSK, 16-QAM, and 64-QAM. Each of these technologies have a scalar radio module, and a corresponding scalar radio medium module (they have ``Scalar`` in their module names; the corresponding radio and radio medium modules should be used together).

.. The scalar analog representation also models features of protocols such as preamble duration, head length, bitrate and modulation type. These can be set with parameters of the radio modules; in ApskScalarRadio, these parameters are set directly; in Ieee80211ScalarRadio, one should set the :par:`channelNumber` and :par:`opMode` (a, b, g, n, etc.) parameters.

**V3** The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth,
and models protocol features such as preamble duration, head length, bitrate and modulation. It also models attenuation, and calculates a signal-to-noise-interference ratio (SNIR) value at reception. Error models can calculate bit error rate and packet error rate of receptions from the SNIR, center frequency, bandwidth, and modulation.

Signals are represented with a boxcar shape in frequency and time. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

.. **V3/2** Signals are represented with a boxcar shape in frequency and time. When simulating interference/concurrent transmissions, signals can either completely overlap (same center frequency and bandwidth; signals interfere), or not overlap at all (no interference). The model cant simulate partially overlapping spectrums (results in an error) or realistic signal shapes in frequency and time.

.. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

.. it just simulates a boxcar signal in frequency and time. These can either completely overlap (interference) or not at all (no interference). it cant simulate partially overlapping spectrums or realistic signal shapes both in frequency and time.

INET contains scalar versions of wireless technologies, such as IEEE 802.11 and 802.15.4; it also contains the scalar version of ApskRadio, which is a generic radio featuring different modulations such as BPSK, 16-QAM, and 64-QAM. Each of these technologies have a scalar radio module, and a corresponding scalar radio medium module (they have ``Scalar`` in their module names; the corresponding radio and radio medium modules should be used together).

The scalar analog representation also models features of protocols such as preamble duration, head length, bitrate and modulation type. These can be set with parameters of the radio modules; in ApskScalarRadio, these parameters are set directly; in Ieee80211ScalarRadio, one should set the :par:`channelNumber` and :par:`opMode` (a, b, g, n, etc.) parameters.
**TODO** also set centerfrequency bandwidth with parameters



..  so

  - parameters of scalar radio modules

  There are various scalar radio and radio medium modules available in INET, such as TODO. The radios have parameters for power, center frequency and bandwidth, and other stuff...like the wifi radios have channel number, opmode, others have modulation etc

    so

    - there are radio and radio medium modules which use the scalar analog model...they have Scalar in their name
    - they should be used together based on the name (Ieee80211ScalarRadio/Ieee80211ScalarRadioMedium, ApskScalarRadio/ApskScalarRadioMedium, etc)
    - the radio has parameters like power, center frequency and bandwidth...sometimes these are set automatically like in Wifi (so you just specify a channel and an opmode)
    - there are other parameters, like preamble duration, bitrate, etc...in wifi you just choose the opmode
    - check the ned documentation of the various modules

.. INET contains various radio and radio medium modules for different wireless technologies which use the scalar analog model; these modules have ``Scalar`` in their names, e.g. Ieee80211ScalarRadio, Ieee802154NarrowbandScalarRadio, AspkScalarRadio. The scalar radio types should be used with the corresponding radio medium module, e.g. Ieee80211ScalarRadio/Ieee80211ScalarRadioMedium, ApskScalarRadio/ApskScalarRadioMedium. The radio modules have parameters like power, center frequency and bandwidth, bitrate, preambleduration, etc. Some modules set these automatically, e.g. in Ieee80211ScalarRadio, one sets the :par:`opMode` (g,n(mixed),ac,etc) and channelNumber parameters, and the module sets the bandwidth, center frequency, and other parameters of transmitters and receivers automatically according to the IEEE 802.11 standard. In ApskScalarRadio, it should be set manually.

.. **TODO** a list of modules

.. In the example simulation, an :ned:`AdhocHost` sends UDP packets to another. The hosts have a distance...

In the example simulation, an :ned:`AdhocHost` sends UDP packets to another. The source host is stationary, the destination host moves away from the source host. As the distance increases between them, the SNIR and packet error rate increase, so as the number of successfully received transmissions.

.. TODO this should be a study...no need for any video just a chart...received packets vs distance/SNIR vs distance?

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :start-at: Config Distance4
   :end-at: channelAccess
   :language: ini

The source host is configured to use the default 802.11g mode, and 54Mbps data rate.

Here is a video of the simulation (successful link-layer transmissions are indicated with arrows; incorrectly received packets are indicated with packet drop animations):

.. video:: media/Distance4.mp4
   :width: 100%

.. normal run, playback speed 1, animation speed 0.1, run until 6.5s

As the distance increases between the two hosts, the packet error rate and the SNIR increase, and packets are dropped.
Note that the communication range of the source host is indicated with a blue circle. Beyond the circle, transmissions cannot be received correctly, and as an optimization, the radio medium module doesn't send them to the destination host, thus there are no packet drop animations.

Dimensional Example: Interference from a Periodic Noise Source
--------------------------------------------------------------

.. - this example is about dimensional
  - why is it good for this purpose? cos need to model the spectrums accurately. there are two channels which overlap, the noise generator has a different spectrum, and short transmissions which might not be enough in time to corrupt the wifi nodes' transmissions
  - parameters, available models
  - drawbacks/benefits/degrees of freedom
  - config/network
  - results (spectrum figure, spectrogram, inspector)

.. The dimensional analog model is the most sophisticated analog signal representation in INET. It can model arbitrary signal shapes in frequency and time. It can also model interference more realistically than the scalar model. /It can model interference even between different technologies (cross-technology interference). It can simulate partially overlapping signals in frequency and time. The spectrums can also be visualized with spectrum figures and spectrograms and power density map...

.. **V1** The dimensional analog model represents signal power as a multi-dimensional function of time and frequency. It can model arbitrary signal shapes in frequency and time, simulate interference of signals with partially overlapping spectrums, and also simulate interference of different wireless technologies (cross-technology interference). It is the most accurate analog signal representation, but its performance is similar to the scalar model/but it also requires the most computing power. The signal spectrums of the dimensional analog model can also be visualized with spectrum figures, spectrograms and power density maps (see TODO).

.. **V2** The dimensional analog model represents signal power as a multi-dimensional function of time and frequency. It can model arbitrary signal shapes in frequency and time. It can be used to simulate complex signal interactions, i.e. multiple arbitrary signal shapes in frequency and time can overlap to any degree in frequency and time.

The dimensional analog model represents signal power as a multi-dimensional function of time and frequency. It can:

- Model arbitrary signal shapes in frequency and time
- Simulate complex signal interactions, i.e. multiple arbitrary signal shapes in frequency and time can overlap to any degree in frequency and time
- Simulate interference of different wireless technologies (cross-technology interference)

It is the most accurate analog signal representation, but its performance is comparable to that of the scalar model. The signal spectrums of the dimensional analog model can also be visualized with spectrum figures, spectrograms and power density maps (see TODO).

.. **V4** The dimensional analog model represents signal power as a multi-dimensional function of time and frequency. It can model arbitrary signal shapes in frequency and time, simulate interference of signals with partially overlapping spectrums, and also simulate interference of different wireless technologies (cross-technology interference). It is the most accurate analog signal representation, as more complex signal interactions can be simulated. but its performance is similar to the scalar model/but it also requires the most computing power. The signal spectrums of the dimensional analog model can also be visualized with spectrum figures, spectrograms and power density maps (see TODO).

.. **TODO** its more accurate because arbitrary interference can be simulated, i.e. multiple arbitrary signals shapes can overlap to various degrees/any degree in frequency and time. -> thus more complex signal interactions

.. the drawback is performance, everything else is a benefit...accuracy

.. The dimensional analog model uses a multi-dimensional function API to

  - represent signals as multi-dimensional functions (power density vs time and frequency)
  - create signal representation with composition of function primitives/primitives and composition
  - create signal representation by composition of primitives
  - available functions:
    - boxcar function
    - linear function
    - interpolated function
    - multiplication/division/addition/substration -> to model snir, attenuation
    - shift function -> to shift a signal shape in time and frequency
    - get the min, max, mean and integral of functions over a multi-dimensional interval
    - partitioning -> composition of complex signal shapes from primitive functions (such as constant, linear, interpolated, reciprocal, etc)
    - domainlimit?, boxcar, shift, approximate, integrate, (memoize)

.. The dimensional analog model uses a multi-dimensional mathemitical API to create signal representations. Signals are represented as a multi-dimensional function, i.e. power density over time and frequency. Arbitrary signal shapes/functions can be created using primitives and composition, and various other functions:

  - primitives:

    - constant over all dimensions
    - **linear**: linear in 1 dimension, constant in the others
    - **bilinear**: linear in 2 dimensions, constant in the other
    - **reciprocal**: reciprocal in 1 dimension, constant in the others

  - functions that work on primitives:

    - **limit domain**: limit the function domain in 1 or 2 dimensions/from left, right or both?
    - **boxcar function**: constant + limit domain? is that already a composite?
    - **shift**: shift the function in time or frequency
    - **approximate**: approximate function at arbitrary points using interpolation
    - **integrate**: integrate function over a multi-dimensional interval (e.g. to get signal power)
    - get **min**, **max**, **mean** over a multi-dimensional interval (e.g. for calculating snir)
    - **add/substract**: for calculating interference
    - **multiply**: for applying transmission power, calculating attenuation
    - **divide**: for calculating snir
    - **partitioning**: composition of complex functions from primitives

  it works like this:

  | /--\\ -> the function

  - domain limited linear + constant boxcar + domain limited linear
  - shift in time to account for propagation duration
  - shift in frequency to actual wifi channel
  - multiply by transmission power
  - multiply by attenuation
  - divide by background noise power density
  - apply getMin to get minSnir?
  - also integrate over the domain to get transmission power at reception (for some reason)

  The Ieee80211DimensionalTransmitter in INET uses this API to create transmissions.
  And the thing in the ini file is just syntactic salt

.. --------

The multi-dimensional analog model uses an efficient generic purpose multi-dimensional mathematical function API. The analog model represents signal spectral power density [W/Hz] as a multi-dimensional function of time [s] and frequency [Hz].

The API provides primitive functions (e.g. constant function), function compositions (e.g. function addition), and allows creating new functions either by implementing the required C++ interface or by combining existing implementations.
Here are some example functions provided by the API:

Primitive functions:

- Multi-dimensional constant function
- Multi-dimensional unilinear function, linear in 1 dimension, constant in the others
- Multi-dimensional bilinear function, linear in 2 dimensions, constant in the others
- Multi-dimensional unireciprocal function, reciprocal in 1 dimension, constant in the others
- Boxcar function in 1D and 2D, being non-zero in a specific range and zero everywhere else
- Standard gauss function in 1D
- Sawtooth function in 1D that allows creating chirp signals
- Interpolated function with samples on a grid in 1D and 2D
- Generic interpolated function with arbitrary samples and interpolations between them

Function compositions:

- Algebraic operations: addition, subtraction, multiplication, division
- Limiting function domain, shifting function domain, modulating function domain
- Combination of two 1D functions into a 2D function
- Approximation in selected dimension
- Integration in selected dimension

Interpolators:

- Left/right/closer (between two points, use the value of the left/right point, or use the left value until the middle of the interval, and the right value after that)
- Min/max/average
- Linear

.. **V1** The API is used by dimensional transmitters and receivers. Here are some examples:

  - The boxcar function can be used to create signals with a specific bandwidth
  - The domain shifting function is used to place signals on the frequency spectrum,
    and shift them to the appropriate time when they are transmitted
  - Multiplication can be used to apply transmission power and attenuation
  - Addition can be used to sum interfering signals
  - Division can be used to calculate SNIR by dividing the received signal with interfering signals
  - Partitioning can be used to construct complex signals in frequency and time from primitives

.. The dimensional transmitters in INET use the API to create transmissions. For example, The boxcar function can be used to create signals with a specific bandwidth. The domain shifting function is used to place signals on the frequency spectrum, and to the appropriate point in time. Transmission power and attenuation is applied with the multiplication function. Interfering signals are summed with the addition function. SNIR is calculated by dividing the received signal with interfering signals.
   Signals with a complex spectrum are constructed from primitives with the partitioning function.

.. **V2** The dimensional transmitters in INET use the API to create transmissions. For example:

  - The boxcar function can be used to create signals with a specific bandwidth.
  - The domain shifting function is used to place signals on the frequency spectrum, and to the appropriate point in time.
  - Transmission power and attenuation is applied with the multiplication function.
  - Interfering signals are summed with the addition function.
  - SNIR is calculated by dividing the received signal with interfering signals.
  - Signals with a complex spectrum are constructed from primitives with the partitioning function.

The dimensional transmitters in INET use the API to create transmissions. For example:

- The 2D boxcar function is used to create a flat signal with a specific bandwidth and duration.
- The domain shifting function is used to place it on the frequency spectrum, and to the appropriate point in time.
- Transmission power and attenuation is applied with the multiplication function.
- Transmission power is applied with the multiplication function.
- Attenuation is also applied with the multiplication function (it's more complicated, as attenuation is space, time and frequency dependent, and takes obstacles into account).
- Interfering signals are summed with the addition function.
- SNIR is calculated by dividing the received signal with interfering signals.

The transmitter in INET uses the most optimal functions to create the signal, depending on the gain parameters. For example,
if the parameters describe a flat signal, it'll use a boxcar function (in 1D or 2D, whether the signal is flat in one or two dimensions). If the gain parameters describe a complex function, it'll use the generic interpolated function; the gain parameter string actually maps to the samples and the types of interplation between them. **TODO**

.. - Signals with a complex spectrum are constructed from primitives with the partitioning function.

INET contains the dimensional version of IEEE 802.11, narrowband and ultra-wideband 802.15.4, and Apsk radio (the 802.15.4 ultra-wideband version is only available in dimensional form). TODO parameters

.. --------

  this is good because its nearly has the same performance as the scalar
  but it is more complex, there is composition
  better accuracy...can be extended with the API
  can make use of better error models
  actually can simulate per symbol snir

.. The dimensional analog model has comparable performance to the scalar model, but it is more
   accurate and can model interference with partially overlapping spectrums.

  so what i wanna say is

  The dimensional analog model uses the api to create signals, and transmitters use that to create signals?

  so actually in ieee80211dimesionaltransmitter, there is a line which uses this api to create the signal

  so the dimensional analog model is in the radio medium module and the transmitters just create
  dimensional transmissions and that is part of the dimensional model

    so

    - the dimensional analog model represents signals a multi-dimensional function of power vs time and frequency
    - it can model realistic/arbitrary signal shapes in frequency and time
    - it can simulate partially overlapping signals in frequency and time/partially overlapping signal spectrums
    - it can simulate interference even between different technologies (cti)
    - it is the most accurate
    - the only drawback is performance
    - the spectrums can be visualized

    - how to define signal shapes
    - the listening part/other parts can still cause interference
    - minSnir/meanSnir

    - types

**TODO** normalization parameters

.. The signal shapes can be configured using the :par:`timeGains` and :par:`frequencyGains` parameters of dimensional transmitters.

.. **TODO** briefly about the syntax

.. The signal shape in frequency can be defined by values of frequency-gain pairs; a pair defines a point on the frequency-power diagram/graph. The interpolation mode between two points can be specified with keywords between two frequency-gain pairs, such as TODO.

  INET contains dimensional versions of IEEE 802.11 and 802.15.4, and Apsk radio, and the corresponding radio medium modules.

.. For example, signal shapes in frequency can be defined as follows:

.. - the spectrum is specified as points in the frequency-power graph
  - a point is specified with a frequency-gain pair
  - interpolation of the spectrum function is specified between points with keywords (such as linear, left, right, etc)

The signal shapes in frequency and time can be defined with the :par:`frequencyGains` and :par:`timeGains` parameters of transmitter modules.
Here is an example signal spectrum definition:

.. code-block:: ini

   **.frequencyGains = "left c-b*1.5 -40dB linear c-b -28dB linear c+b -28dB linear c+b*1.5 -40dB right"

Briefly about the syntax (applies to the :par:`timeGains` parameter as well):

.. including 'Briefly about the syntax:' section from Coexistence

.. include:: ../../coexistence/doc/index.rst
   :start-after: Briefly about the syntax:
   :end-before: For more on the syntax

The parameter value above describes the following spectrum (displayed on a spectrum figure):

.. figure:: media/spectrum.png
   :width: 50%
   :align: center

Note that even though the interpolation between the points is linear, it appears curved due to the log scale used on the spectrum figure.

In the example simulation, there are two host-pairs; one host in each pair sends UDP packets to the other. The host pairs are on different, slightly overlapping Wifi channels. A noise source (:ned:`NoiseSource`) creates small bursts of noise periodically, which overlaps with both host pair's transmissions.

The :ned:`noiseSource` module creates dimensional transmissions, which interfere with other signals. It contains a transmitter module (:ned:`NoiseDimensionalTransmitter`), an antenna module (:ned:`IsotropicAntenna` by default), mobility module (so that it has a position, and optinally move around):

.. figure:: media/noisesource.png
   :width: 25%
   :align: center

The noise transmissions don't have any data or modulation, just a center frequency, bandwidth, power, and configurable arbitrary signal shape in frequency and time. It also has duration and sleep interval parameters.

Here is the configuration in omnetpp.ini pertaining to the radio settings:

.. (the visualizer settings are omitted)

.. literalinclude:: ../omnetpp.ini
   :start-after: radio settings
   :end-at: powerSpectralDensity
   :language: ini

The hosts are configured to have :ned:`Ieee80211DimensionalRadio`. They are put on slightly overlapping Wifi channels. The signal spectrums are configured to be the spectral mask of OFDM transmissions in the 802.11 standard.

.. **TODO** snirMode

.. **TODO** snirMode

In the receiver, reception of frames with SNIR under the SNIR threshold are not attempted.
The :par:`snirThresholdMode` parameter in the receiver specifies how the SNIR is calculated; it's either ``min`` or ``mean``, i.e. take the minimum or the mean of the SNIR during the course of receiving a frame. Similarly, the :par:`snirMode` parameter in the receiver's ``errorModel`` submodule specifies whether to take into account the ``min`` or ``mean`` of SNIR when calculating reception probability. **TODO** limitations of the current error model -> not sure if its needed

.. **TODO** when to use which one?

.. **TODO** include the relevant part from spectrum ?

.. .. include:: ../../coexistence/doc/index.rst
   :start-after: the reception.
   :end-before: We set the

.. include:: ../../coexistence/doc/index.rst
   :start-after: either ``min`` or ``mean``.
   :end-before: We set the

.. **TODO** why we use mean here ?

We use mean SNIR because the noise bursts are short compared to the hosts' transmissions, and it wouldn't be realistic if the short bursts ruined the longer data frames.

.. **TODO** describe the noise source

  - it creates dimensional transmissions
  - it has a transmitter, an antenna and a mobility module (so it has position)(or it can move)
  - the transmissions dont have any data or modulation, just center frequency, bandwidth, and can have arbitrary shape in frequency and time
  - it interferes with other transmissions
  - it has a power, duration and sleep interval parameter

.. **TODO** noiseSource

The noise source is configured to create noise transmissions which overlap both host pair's Wifi channels.
Background noise is specified as power density, instead of power. **TODO** this is important because the transmissions are defined that way as well ?

.. **TODO** background noise

.. INET contains dimensional versions of IEEE 802.11 and 802.15.4, and Apsk radio.

Here is a video of the simulation. Signals are visualized with colored rings, successful PHY and datalink-layer transmissions are visualized with arrows. The signals are displayed with spectrum figures and spectrograms:

.. video:: media/noise1.mp4
   :width: 100%

.. animation speed none, playback speed 0.25, zoom 3.71, normal run from event 299 to 518
   hide physical and data link visualizers until around event 334

The noise transmissions often overlap the data frames, yet the short bursts are not enough to ruin their reception, most packets are successfully received. Note that the thin line of the noise on the spectrogram is much shorter than the data frame. Also, the spectrograms have a colored background due to the background noise (also displayed on the spectrum figures).
