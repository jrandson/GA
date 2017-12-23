import matplotlib.pyplot as plt




def plot_tempo_ga():
	pop = [30, 60, 90, 120]
	tempo = [16.03, 32.30, 47.79, 63.32]
	tempo =[i*0.5 for i in tempo]
	plt.title('Tempo de execucao do GA pelo tamanho da populacao, fitness de 1 dimensao, 16 bits')
	plt.plot(pop, tempo,'r*-')
	plt.ylabel('Tempo (ms)')
	plt.xlabel('Tamnho da populacao')
	plt.show()

def plot_best_gen():
	f = file('best.txt');
	x = []
	y = []
	for line in f:
		data = line.split(':')
		x.append(data[0])
		y.append(data[1])


	plt.plot(x,y,'r*-')
	plt.ylabel('best by generations')
	plt.show()

plot_best_gen()