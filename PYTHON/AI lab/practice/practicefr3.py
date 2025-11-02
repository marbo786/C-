def count_words(sentence):
    counts = {}
    for word in sentence.split():
        # .get(word, 0) returns 0 if word is not yet in counts
        counts[word] = counts.get(word, 0) + 1
        print(counts)
    
count_words(sentence= "hello my name is mohsin saeed hello")