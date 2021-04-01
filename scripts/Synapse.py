from random import randint, uniform, seed
from neuron import h, gui
from neuron.units import ms, mV
import matplotlib.pyplot as plt
from matplotlib import style
from matplotlib import style, rc
import numpy as np
import pickle

class Synapse:

    num_synapses = 0
    gmax_AMPA = 0.001 * 100
    gmax_NMDA = 0.7 * 0.001 * 100

    stimulator = h.VecStim()
    spike_times = list(range(950, 3000, 200))
    spikes_vector = h.Vector(spike_times)


    def __init__(self, loc):
        '''Create AMPA/NMDA synapse at given location ('loc' argument)
        '''
        self.loc = loc # location of the synapse
        #self.spike_times = list(range(500, 1000, 20)) + list(range(4000, 8000, 60))
        self.GluSyn = h.SimpleAMPA_NMDA(self.loc)
        self.GluSyn.gmax_AMPA = Synapse.gmax_AMPA
        self.GluSyn.gmax_NMDA = Synapse.gmax_NMDA
        Synapse.num_synapses += 1

        self.connection = h.NetCon(Synapse.stimulator, self.GluSyn)
        self.connection.weight[0] = 1

    def __repr__(self):
        return 'Synapse[{}]'.format(self.loc)


    @classmethod
    def setup_gmax(cls, gmax_AMPA_new=0, gmax_NMDA_new=0):
        '''updates AMPA and NMDA coductances
        '''
        Synapse.gmax_AMPA = gmax_AMPA_new
        Synapse.gmax_NMDA = gmax_NMDA_new


    @classmethod
    def play_stimulation(cls):
        '''Presynaptic stimulation of all Synapse instances
        '''
        cls.stimulator.play(cls.spikes_vector)


    @classmethod
    def restore_defaults(cls):
        '''restores default conductances and synapse counter (num_synapses)
        '''
        Synapse.gmax_AMPA = 0.001 * 100
        Synapse.gmax_NMDA = 0.7 * 0.001 * 100


    @classmethod
    def create_synapses(cls, seed_value=666, locs=None, num_rand_locs=None) -> 'synapses instances':
        '''Method for creating  synapses at given locations
        '''
        Synapse.restore_defaults()
        if locs:
            Synapse.setup_gmax(gmax_AMPA_new = Synapse.gmax_AMPA / len(locs),
                               gmax_NMDA_new = Synapse.gmax_NMDA / len(locs))
            syns = [cls(h.apical_dendrite[loc](0.5)) for loc in locs]
            return syns
        if num_rand_locs:
            seed(seed_value)
            if num_rand_locs > 300:
                raise ValueError('No more than 300 synapses are allowed. %s were given' % num_rand_locs)
            # changes NMDA and AMPA coductances proportionally to num_rand_locs
            # to satisfy constant total coductance for any no. of synapses
            Synapse.setup_gmax(gmax_AMPA_new = Synapse.gmax_AMPA / num_rand_locs,
                               gmax_NMDA_new = Synapse.gmax_NMDA / num_rand_locs)
            syns = [cls(h.apical_dendrite[randint(0, 118)](uniform(0, 1))) for i in range(num_rand_locs)]
            return syns

