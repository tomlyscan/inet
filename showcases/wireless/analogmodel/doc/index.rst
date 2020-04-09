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

In INET, radio signal analog models represent signals as they are transmitted, received and propagate in the wireless medium. Models of different complexity are available, suitable for different purposes.

This showcase describes the avaialbe analog signal representation models, their advantages and drawbacks, and typical use cases. There are three example simulations for typical use cases.

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

- **Unit disk**: Simple model featuring only communication range and interference range as parameters. Reception in communication range is always successful, and outside of it always unsuccessful. Signals can be detected in the interference range, which might cause network nodes to defer from transmitting. Suitable for simulations where the emphasis is not on the details of radio transmissions, but something else, e.g. testing routing protocols.
- **Scalar**: Signal power is represented by a scalar value. Transmissions have a center frequency and bandwidth. **TODO** attentuation due to distance or other stuff Signal interfere when their center frequency and bandwidth is exactly the same (and the signal power is high enough TODO). When there is no overlap in the frequency spectrum, they don't interfere. Overlapping signals can't be simulated with this model, it throws and error. **TODO** suitable for what
- **Dimensional**: Signal power is represented as a multidimensional function of frequency and time; arbitrary signal shapes can be defined in time and the frequency spectrum. Attenuation and interference is modeled accurately. Suitable for simulating cross-technology interference (**TODO** see also Coexistence) **TODO** suitable for accurate interference and CTI simulation

More complex models are more accurate but require more computing performance.
INET contains a version of radio and radio medium module for each type and technology, e.g. :ned:`Ieee80211UnitDiskRadio`/:ned:`UnitDiskRadioMedium`, :ned:`ApskScalarRadio`/:ned:`ApskScalarRadioMedium`,
:ned:`Ieee802154NarrowbandDimensionalRadio`/:ned:`Ieee802154NarrowbandDimensionalRadioMedium`, etc.
**TODO** these models use the appropriate analog signal representation (i.e. the receiver, the transmitter, and the radio medium)

    so

    - signal power is represented as a function of frequency and time
    - arbitrary signal shape can be defined in frequency and time
    - its a multi dimensional function
    - attenuation, signal spectrum and interference is modeled accurately
    - can model CTI -> can the scalar model cti ?

    so

    there are types as in unit disk, scalar and dimensional
    and also types as in ieee80211, apsk, ieee802154 etc

    There are several

Testing routing protocols (Unit disk)
-------------------------------------

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

**V1** In this scenario, the emphasis is on the connectivity of the source and destination hosts,

**V2** This scenario examines the connectivity of the source and destination hosts,

i.e. how the moving intermediate hosts can build temporary routes and relay the ping messages. In this context, the communication ranges of the hosts is an adequate abstraction of the physical layer communication, thus unit disk analog model is suitable for this purpose.

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :start-at: Config Routing3
   :end-at: displayCommunicationRanges
   :language: ini

.. - sometimes there is connectivity between the two hosts
   - sometimes there isnt

Here is a video of the simulation running (successful ping message sends between the source and destination hosts are indicated with colored arrows; routes to destination are indicated with black arrows):

TODO

.. TODO display just the routes

The source and destination hosts are connected intermittently. If the intermediate nodes move out of range before the routes can be built then there is no connectivity. This can happen if the nodes move too fast, as route formation takes time due to the AODV protocol overhead.

.. - this can be used to run simulations to figure out how fast the nodes can move so that connectivity can be maintained
   - as the AODV protocol has overhead
   - if the intermediate nodes move out of range before the routes can be built then there would be no connectivity

   - this should be in the intro part of this section ?

Number of received packets vs distance (Scalar)
-----------------------------------------------

- this example is about the scalar
- why is t his good for this purpose? cos we need the attenuation/the reception needs to depend on the power levels
- drawbacks/benefits/degrees of freedom
- parameters, available models
- config/network
- results (show the BER/PER/number of packets)(should a study?)

**V1** The scalar analog model represents transmissions with a scalar power value, a center frequency and a bandwidth, and might include other protocol features as well **TODO**. **TODO** there is also modulation.
The scalar representation can model attenuation, and is able to compute a signal-to-noise-interference radio (SNIR). The SNIR is used by error models to calculate bit-error-rate and packet-error-rate. **TODO** this is a benefit...a limitation is that it cant simulate partially overlapping spectrums or realistic signal shapes both in frequency and time. it just simulates a boxcar signal in frequency and time. These can either completely overlap (interference) or not at all (no interference).

**TODO** types

--------

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

**V2** The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth; it models attenuation. It uses these to calculate a signal-to-noise-interference ratio (SNIR) at reception. The SNIR can be used by error models to calculate bit error rate and packet error rate of receptions.

Signals are represented with a boxcar shape in frequency and time. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

INET contains scalar versions of wireless technologies, such as IEEE 802.11 and 802.15.4; it also contains the scalar version of ApskRadio, which is a generic radio featuring different modulations such as BPSK, 16-QAM, and 64-QAM. Each of these technologies have a scalar radio module, and a corresponding scalar radio medium module (they have ``Scalar`` in their module names; the corresponding radio and radio medium modules should be used together).

The scalar analog representation also models features of protocols such as preamble duration, head length, bitrate and modulation type. These can be set with parameters of the radio modules; in ApskScalarRadio, these parameters are set directly; in Ieee80211ScalarRadio, one should set the :par:`channelNumber` and :par:`opMode` (a, b, g, n, etc.) parameters.

**V3** The scalar analog model represents signals with a scalar signal power, a center frequency and a bandwidth,
and models protocol features such as preamble duration, head length, bitrate and modulation. It also models attenuation, and calculates a signal-to-noise-interference ratio (SNIR) value at reception. Error models can calculate bit error rate and packet error rate of receptions from the SNIR, center frequency, bandwidth, and modulation.

**V3/1** Signals are represented with a boxcar shape in frequency and time. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

**V3/2** Signals are represented with a boxcar shape in frequency and time. When simulating interference/concurrent transmissions, signals can either completely overlap (same center frequency and bandwidth; signals interfere), or not overlap at all (no interference). The model cant simulate partially overlapping spectrums (results in an error) or realistic signal shapes in frequency and time.

.. The model can simulate interference when the interfering signals have the same center frequency and bandwidth, and spectrally independent transmisssions when the spectrums don't overlap at all; partially overlapping spectrums are not supported by this model (and result in an error).

.. it just simulates a boxcar signal in frequency and time. These can either completely overlap (interference) or not at all (no interference). it cant simulate partially overlapping spectrums or realistic signal shapes both in frequency and time.

INET contains scalar versions of wireless technologies, such as IEEE 802.11 and 802.15.4; it also contains the scalar version of ApskRadio, which is a generic radio featuring different modulations such as BPSK, 16-QAM, and 64-QAM. Each of these technologies have a scalar radio module, and a corresponding scalar radio medium module (they have ``Scalar`` in their module names; the corresponding radio and radio medium modules should be used together).

The scalar analog representation also models features of protocols such as preamble duration, head length, bitrate and modulation type. These can be set with parameters of the radio modules; in ApskScalarRadio, these parameters are set directly; in Ieee80211ScalarRadio, one should set the :par:`channelNumber` and :par:`opMode` (a, b, g, n, etc.) parameters.



  so

  - parameters of scalar radio modules

  There are various scalar radio and radio medium modules available in INET, such as TODO. The radios have parameters for power, center frequency and bandwidth, and other stuff...like the wifi radios have channel number, opmode, others have modulation etc

    so

    - there are radio and radio medium modules which use the scalar analog model...they have Scalar in their name
    - they should be used together based on the name (Ieee80211ScalarRadio/Ieee80211ScalarRadioMedium, ApskScalarRadio/ApskScalarRadioMedium, etc)
    - the radio has parameters like power, center frequency and bandwidth...sometimes these are set automatically like in Wifi (so you just specify a channel and an opmode)
    - there are other parameters, like preamble duration, bitrate, etc...in wifi you just choose the opmode
    - check the ned documentation of the various modules

INET contains various radio and radio medium modules for different wireless technologies which use the scalar analog model; these modules have ``Scalar`` in their names, e.g. Ieee80211ScalarRadio, Ieee802154NarrowbandScalarRadio, AspkScalarRadio. The scalar radio types should be used with the corresponding radio medium module, e.g. Ieee80211ScalarRadio/Ieee80211ScalarRadioMedium, ApskScalarRadio/ApskScalarRadioMedium. The radio modules have parameters like power, center frequency and bandwidth, bitrate, preambleduration, etc. Some modules set these automatically, e.g. in Ieee80211ScalarRadio, one sets the :par:`opMode` (g,n(mixed),ac,etc) and channelNumber parameters, and the module sets the bandwidth, center frequency, and other parameters of transmitters and receivers automatically according to the IEEE 802.11 standard. In ApskScalarRadio, it should be set manually.

**TODO** a list of modules

In the example simulation, an :ned:`AdhocHost` sends UDP packets to another. The hosts have a distance...

TODO this should be a study...no need for any video just a chart...received packets vs distance/SNIR vs distance?

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :start-at: Config Distance2
   :end-before: Config Noise
   :language: ini

Interference from a periodic noise source (Dimensional)
-------------------------------------------------------

- this example is about dimensional
- why is it good for this purpose? cos need to model the spectrums accurately. there are two channels which overlap, the noise generator has a different spectrum, and short transmissions which might not be enough in time to corrupt the wifi nodes' transmissions
- parameters, available models
- drawbacks/benefits/degrees of freedom
- config/network
- results (spectrum figure, spectrogram, inspector)
