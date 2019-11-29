import json
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import imageio
import os
import time
from progress.bar import FillingCirclesBar

def get_params(params_file):
	params_list = np.loadtxt(params_file, skiprows=1)
	params = {}
	params['steps'] = params_list[0]
	params['dt'] = params_list[1]
	params['dx'] = params_list[2]
	params['L'] = params_list[3]
	params['N'] = params_list[4]
	params['tmax'] = params_list[8]
	params['eta'] = params_list[6]
	return params

def make_video(params_file='output/params.txt', phi_file='output/phi.txt', x_file='output/x.txt', gifname='movie.gif', duration=0.1, xkcd=False):
	params = get_params(params_file)
	phi_array = np.loadtxt(phi_file)
	x_array = np.loadtxt(x_file)
	solution = {'u': phi_array, 'x': x_array}
	step = int(0.01/params['dt'])
	bar = FillingCirclesBar('Loading', suffix='%(percent)d%%', max=int((params['steps'] - 1)/step))
	images = []
	figsize = (6, 6)
	for subplot in range(1, int(params['steps']), step):
		if xkcd:
			plt.rcParams['text.usetex'] = False
			plt.xkcd()
		fig = plt.figure(figsize=figsize)
		ax = plt.subplot(1, 1, 1)
		plt.sca(ax)
		plt.plot(solution['x'], solution['u'][subplot - 1, :],
			c='#F61067',
			lw=3.5)
		plt.ylim(-1.5 * params['eta'], 1.5 * params['eta'])
		if xkcd:
			plt.xlabel(r'x')
			plt.ylabel(r'u(x, t)')
		else:
			plt.xlabel(r'$x$')
			plt.ylabel(r'$\phi(x, t)$')
		plt.title('t = {:.2f}s'.format((subplot - 1) * params['dt']))
		if subplot > 1:
			plt.axis(axis)
		if subplot == 1:
			axis = plt.axis()
		filename = 'temp.png'
		plt.savefig(filename)
		plt.close()
		images.append(Image.open(filename))
		os.remove(filename)
		bar.next()
	bar.finish()
	print('', end='\r\r')
	if xkcd:
		imageio.mimsave('xkcd_' + gifname, images, duration=duration)
	else:
		imageio.mimsave(gifname, images, duration=duration)

if __name__ == '__main__':
	make_video()