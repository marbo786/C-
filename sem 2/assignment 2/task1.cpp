#include <iostream>
#include <string>

using namespace std;


class character {


    protected: 

    string name;
    int level;
    int healthpoints;

    public: 

    character(string name, int level) : name(name), level(level), healthpoints(100) {}

        
        virtual void displayinfo() {

            cout << "name: " << name << ", level: "<< level<< ", healthpoints: "<<healthpoints<<endl;
        }
        
        friend void battle(character& player , character& opponent);

    };


class warrior : public character {

    private:

    int strength;
    int armour;

    public: 

    warrior(string name, int level, int strength, int armour) : character(name, level), strength(strength), armour(armour) {}

    void displayinfo() override {

        character::displayinfo();
        cout<< "class: warrior , strength: "<< strength << ", armour: "<< armour <<endl;
    }


    int get_strength() const { return strength; }
    int get_armor() const { return armour; }

};


class Mage : public character 
{
    private:
        int intelligence;
        int mana;
    
    public:
       
        Mage(string name, int level, int intelligence, int mana) : character(name, level), intelligence(intelligence), mana(mana) {}
    
        
        void displayinfo() override {
            character::displayinfo();
            cout << "Class: Mage, Intelligence: " << intelligence << ", Mana: " << mana << endl;
        }
    
       
        int get_intelligence() const { return intelligence; }
    };
    

    class Rogue : public character {
        private:
            int agility;
            int evasion;
        
        public:
            
            Rogue(string name, int level, int agility, int evasion) : character(name, level), agility(agility), evasion(evasion) {}
        
            
            void displayinfo() override {
                character::displayinfo();
                cout << "Class: Rogue, Agility: " << agility << ", Evasion: " << evasion << endl;
            }
        
            
            int get_agility() const { return agility; }
        };

void battle(character& player, character& opponent) {
    int damage = 0;

    // Determine damage based on character type
    if (warrior* w = dynamic_cast<warrior*>(&player)) {
        damage = w->get_strength(); // Damage is equal to strength
    } else if (Mage* m = dynamic_cast<Mage*>(&player)) {
        damage = m->get_intelligence(); // Damage is equal to intelligence
    } else if (Rogue* r = dynamic_cast<Rogue*>(&player)) {
        damage = r->get_agility(); // Damage is equal to agility
    }

    // Apply damage
    opponent.healthpoints -= damage;
    if (opponent.healthpoints < 0) opponent.healthpoints = 0;

    cout << player.name << " attacks " << opponent.name << " for " << damage << " damage!" << endl;
    cout << opponent.name << " now has " << opponent.healthpoints << " health points left." << endl;

    
}

int main(){

    warrior warrior1("ironman", 5, 20, 15);
    Mage mage1("superman", 5, 25, 30);
    Rogue rogue1("daredevil", 5, 18, 20);

    // Display character info
    warrior1.displayinfo();
    mage1.displayinfo();
    rogue1.displayinfo();

    // Simulate a battle
    battle(warrior1, mage1);
    battle(mage1, rogue1);
    battle(rogue1, warrior1);

    return 0;

}