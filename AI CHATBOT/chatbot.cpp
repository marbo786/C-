#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// initialized to an empty string
string lastTopic = "" ;

// taking user input and converting it into lowercase
string tolowercase(string input)
{
// str.begin() function is to return the iteratoring pointer to the beginning of the string
//str.end() function is to return the iteratoring pointer to the end of the string
//we use the str.begin() function again to now store the transformed lowercase characters 
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;

}
// Predefined responses and fun facts
vector <string> funFacts = 
{
    "Did you know? Honey never spoils.",
    "Bananas are berries, but strawberries aren't!",
    "Did you know? Octopuses have three hearts.",
    "A bolt of lightning contains enough energy to toast 100,000 slices of bread.",
    "giki is the Only Major University With A Hiking Trail.",
    "National Icon Abdul Qadeer Khan Was The Project Director of GIKI.",
    "One of the Monuments in giki is Dedicated to a Pilot Who Died Saving the Institute.",
    "Nigar Johar - Only Female General in Pakistan Army History is from swabi."
};

// functionality 1:
string getRandomFunFact()
{
    return funFacts[rand() % funFacts.size()];
}

// getting response based on user input
string userresponse(string input)
{

// we again convert to lowercase to compare input easily.
    input = tolowercase(input); 

//find functions help to search the text quotation in the input
//The comparison != string::npos checks if the return value of find() is not equal to string::npos which is typically defined as the maximum possible value for an index, effectively indicating that the substring does not exist in the string.


if (input.find("hello") != string::npos || input.find("hi") != string::npos || input.find("hey") != string::npos || input.find("yoo") != string::npos)
{
    return "hey how may i help u today?";
}
else if (input.find("how are you") != string::npos)
{
    return "i am doing fantastic! what about you?";
}
else if (input.find("great") != string::npos || input.find("fine") != string::npos)
{
    return "That's awesome to hear!";
}
else if (input.find("funfact") != string::npos || input.find("tell me something interesting") != string::npos)
{
    return getRandomFunFact();
}
        
// Check for sports topic

else if (input.find("sports") != string::npos || input.find("football") != string::npos || 
         input.find("cricket") != string::npos || input.find("basketball") != string::npos || 
         input.find("tennis") != string::npos || input.find("game") != string::npos)
        {
        lastTopic = "sports";
        return "I love talking about sports! Do you want to be see the latest waves in the sports industry?";
        }
else if (lastTopic == "sports" && (input.find("yes") != string::npos || input.find("sure") != string::npos))
        {
        return "You can check the latest sports news at this link: https://www.espn.com";
        }

 // Check for movies topic

else if (input.find("movie") != string::npos || input.find("film") != string::npos || 
          input.find("cinema") != string::npos || input.find("actor") != string::npos || 
          input.find("director") != string::npos)
        {
        lastTopic = "movie";
        return "Movies are fantastic! Do you have any recent favorites?";
        }
// Acknowledging favorite movie

    else if (lastTopic == "movie" && (input.find("like") != string::npos || input.find("favourite") != string::npos)) {
        return "you have great taste in movies.";
    }

 // Check for music topic

else if (input.find("music") != string::npos || input.find("song") != string::npos || 
         input.find("singer") != string::npos || input.find("band") != string::npos || 
         input.find("album") != string::npos || input.find("guitar") != string::npos) 
        {
        lastTopic = "music";
        return "Music is such a great way to express yourself! What kind of genre do you like?";
        }
 // Acknowledging favorite music

    else if (lastTopic == "music" && (input.find("like") != string::npos || input.find("favourite") != string::npos)) {
        return "That's awesome! I love that genre too! ";
    }

 // Check for technology topic
else if (input.find("tech") != string::npos || input.find("computer") != string::npos || 
         input.find("programming") != string::npos || input.find("ai") != string::npos || 
         input.find("technology") != string::npos || input.find("gadget") != string::npos)
         {
        lastTopic = "tech";
        return "Technology is evolving so quickly! Are you interested in any specific tech trends?";
         }

if (input.empty()) {
    return "It seems you didn't type anything!";
}


// backup responses...

vector<string> backupresponse = 
{
    "I'm not quite sure I understand.",
    "Could you rephrase that?",
    "I'm still learning! Can you try asking in a different way?",
    "Hmm... I am not sure how to respond to that yet."
};

// If no keywords match provide a random  response
    return backupresponse[rand() % backupresponse.size()];
}

int main() {
    // Seed for random number generation for varied responses
    srand(time(0));  

    string userinput;
    cout<<"hi my name is marbo and i am ur chatbot!, type 'bye' to exit.\n";

    while (true){
// making it nice for the user in the terminal
        cout<<"you: ";
        getline(cin,userinput);

    if(tolowercase(userinput) == "bye"){

        cout<<"marbo: pleasure talking to you! see you next time.\n";
        break;
    }
    string response = userresponse(userinput);
    cout<<"marbo: "<<response<<endl;

    }
return 0;
}
