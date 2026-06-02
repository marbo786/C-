import random
import matplotlib.pyplot as plt
import copy


CITIES = ['A', 'B', 'C', 'D', 'E']
N = len(CITIES)

DIST = [
    [  0,  12,  10,  19,   8],   
    [ 12,   0,   3,   7,   6],   
    [ 10,   3,   0,   2,  20],   
    [ 19,   7,   2,   0,   4],   
    [  8,   6,  20,   4,   0],   
]


POP_SIZE     = 20
GENERATIONS  = 100
MUTATION_RATE = 0.05
TOURNAMENT_SIZE = 3


def tour_distance(tour):
    total = 0
    for i in range(N):
        total += DIST[tour[i]][tour[(i + 1) % N]]
    return total


def tour_str(tour):
    return ' -> '.join(CITIES[c] for c in tour) + f' -> {CITIES[tour[0]]}'


def init_population():
    population = []
    base = list(range(N))
    for _ in range(POP_SIZE):
        individual = base[:]
        random.shuffle(individual)
        population.append(individual)
    return population


def tournament_selection(population):
    contestants = random.sample(population, TOURNAMENT_SIZE)
    
    winner = min(contestants, key=tour_distance)
    return winner[:]



def order_crossover(parent1, parent2):
  
    size = len(parent1)
    
    cut1 = random.randint(0, size - 2)
    cut2 = random.randint(cut1 + 1, size - 1)

    child = [None] * size

                                                        # Step 1: Copy segment from parent1
    child[cut1:cut2 + 1] = parent1[cut1:cut2 + 1]

                                                        # Step 2: Fill from parent2 in order 
    in_child = set(child[cut1:cut2 + 1])
    fill_pos = [(cut2 + 1 + i) % size for i in range(size - (cut2 - cut1 + 1))]
    p2_order = [city for city in parent2 if city not in in_child]

    for pos, city in zip(fill_pos, p2_order):
        child[pos] = city

    return child


def swap_mutation(tour, mutation_rate):
    
    tour = tour[:]
    if random.random() < mutation_rate:
        i, j = random.sample(range(N), 2)
        tour[i], tour[j] = tour[j], tour[i]
    return tour


def genetic_algorithm():

    population = init_population()
    best_distances = []

    print(f"Cities: {CITIES}")
    print(f"Population: {POP_SIZE} | Generations: {GENERATIONS} | Mutation: {MUTATION_RATE}")
    print("=" * 60)

    for gen in range(1, GENERATIONS + 1):

                                                                 # Evaluate fitness (distance) for all individuals
        fitness_scores = [(tour_distance(ind), ind) for ind in population]

                                                                 # Track best in this generation
        best_dist, best_tour = min(fitness_scores, key=lambda x: x[0])
        best_distances.append(best_dist)

        if gen % 20 == 0:
            print(f"Generation {gen:>3}  |  Best Distance: {best_dist:>6.1f}  |  Tour: {tour_str(best_tour)}")

                                                                # Build next generation (elitism: keep best 1)
        new_population = [best_tour[:]]  

        while len(new_population) < POP_SIZE:
            # Selection
            parent1 = tournament_selection(population)
            parent2 = tournament_selection(population)

            # Crossover 
            child = order_crossover(parent1, parent2)

            # Mutation 
            child = swap_mutation(child, MUTATION_RATE)

            new_population.append(child)

        population = new_population

    # Final best
    final_fitness = [(tour_distance(ind), ind) for ind in population]
    final_dist, final_tour = min(final_fitness, key=lambda x: x[0])

    print("=" * 60)
    print(f"\nFINAL RESULT")
    print(f"Best Tour     : {tour_str(final_tour)}")
    print(f"Best Distance : {final_dist}")
    print("=" * 60)

    return best_distances, final_tour, final_dist


def plot_fitness(best_distances):
    plt.figure(figsize=(9, 5))
    plt.plot(range(1, len(best_distances) + 1), best_distances,
             color='steelblue', linewidth=2, marker='o', markersize=3, markevery=5)
    plt.xlabel("Generation", fontsize=13)
    plt.ylabel("Best Tour Distance", fontsize=13)
    plt.title("GA for TSP – Best Fitness vs Generation", fontsize=14, fontweight='bold')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.savefig("ga_tsp_fitness.png", dpi=150)
    print("\nPlot saved as 'ga_tsp_fitness.png'")
    plt.show()

if __name__ == "__main__":
    best_distances, final_tour, final_dist = genetic_algorithm()
    plot_fitness(best_distances)