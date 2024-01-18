/* Jesus Galindo*/

#include <fstream>

#include "actormovie.h"
#include "BSTree.h"

fstream inputFile;
BSTree<struct actorRec, int> AD;
BSTree<struct movieRec, int> MD;

bool loadFiles();
void actorMenu();
void movieMenu();
void mainMenu();


int main()
{
    if (!loadFiles()) // loadfiles menu
    {
        return -1;
    }
    mainMenu(); // main database menu
    return 0;
}

bool loadFiles()
{
    std::string file, word;
    std::cout << "Enter files for movie and actor database trees."; // prompt user for files
    std::cout << "\n\nEnter actor file: ";
    std::cin >> file;
    inputFile.open(file);
    if (!inputFile) // check file
    {
        std::cout << "\nERROR: Could not open file. Exiting Program...\n\n";
        return false;
    }
    std::cout << "\n\nLoading " << file << "...\n\n"; // prompt file worked
    int counter = 1; // assign a ID number to to each record via counter
    std::getline(inputFile, word);
    while (inputFile.good()) // while there are words to read up to each comma
    {
        actorRec record;
        record.Label = counter;
        std::getline(inputFile, word, ',');
        record.Year = word;
        std::getline(inputFile, word, ',');
        record.Award = word;
        std::getline(inputFile, word, ',');
        record.Winner = word;
        std::getline(inputFile, word, ',');
        if (word[0] == '"')
        {
            std::string tmp;
            std::getline(inputFile, tmp, ',');
            word = word + tmp;
            record.Name = word;
        }
        record.Name = word;
        std::getline(inputFile, word);
        record.Film = word;
        if (record.isEmpty())
        {
            continue;
        }
        AD.addNode(record.Label, record); // add node with ID as key
        AD.setRoot(AD.buildBalancedTree(AD.Root())); // rebalance the tree to fix right side problem with incrementing nodes 
        counter++;
    }
    inputFile.close();

    std::cout << "\nEnter movie file: "; // prompt movie file
    std::cin >> file;
    inputFile.open(file); // read file
    if (!inputFile) // check file
    {
        std::cout << "\nERROR: Could not open file. Exiting Program...\n\n";
        return false;
    }
    std::cout << "\n\nLoading " << file << "...\n\n"; // prompt file worked
    std::getline(inputFile, word);
    counter = 1;
    while (inputFile.good()) // while there are words to read up to each comma
    {
        movieRec record;
        record.Label = counter;
        std::getline(inputFile, word, ',');
        record.Name = word;
        std::getline(inputFile, word, ',');
        record.Year = word;
        std::getline(inputFile, word, ',');
        record.Nominations = word;
        std::getline(inputFile, word, ',');
        record.Rating = word;
        std::getline(inputFile, word, ',');
        record.Duration = word;
        std::getline(inputFile, word, ',');
        record.Genre1 = word;
        std::getline(inputFile, word, ',');
        record.Genre2 = word;
        std::getline(inputFile, word, ',');
        record.Release = word;
        std::getline(inputFile, word, ',');
        record.Metacritic = word;
        std::getline(inputFile, word);
        record.Synopsis = word;
        if (record.isEmpty())
        {
            continue;
        }
        MD.addNode(record.Label, record);
        MD.setRoot(MD.buildBalancedTree(MD.Root())); // rebalance tree for structure to be stable
        counter++;
    }
    inputFile.close();
    return true; // if both files are read return true to contiue to database
}

void mainMenu() // main menu
{
    std::string answer; // string to store user response
    char choice; // char to store user navigation through menu
    std::cout << "\nAcadamy Award Database.\n" << "Choose option (1-3).\n"; // prompt user options in menu
    std::cout << "Press 1 Actor database: \n";
    std::cout << "Press 2 Movie database: \n";
    std::cout << "Press 3 Exit program: \n";
    std::cin >> answer;
    if (answer.length() > 1) // check if user inputed only one char
    {
        std::cout << "\nERROR: Invalid Input.\n";
        mainMenu();
    }
    choice = answer[0];
    switch (choice)
    {
    case '1':
        actorMenu(); // call actor database menu
        break;
    case '2':
        movieMenu(); // call movie database menu
        break;
    case '3':
        return;
        break;
    default:
        std::cout << "\nERROR: Invalid Input.\n";
        mainMenu(); // call error and loop
        break;
    }
}

void actorMenu()
{
    ofstream file; // write to file
    actorRec newrec, tmp; // tmp datatype for manipulation
    std::vector <actorRec> list; // list to sort fields
    std::string answer; // for user answer
    char choice; // for navigating menu
    int num = 0; // integer for ID search
    std::cout << "\nActor Datadabase Menu:\n" << "Choose option (1-7).\n"; // prompt user choices for naviagation
    std::cout << "1. Add new record.\n";
    std::cout << "2. Delete record.\n";
    std::cout << "3. Modify record.\n";
    std::cout << "4. Search record.\n";
    std::cout << "5. Print Records.\n";
    std::cout << "6. Exit to main menu.\n";
    std::cout << "7. Exit program\n";
    std::cin >> answer;
    if (answer.length() > 1) // check if user input a string of chars
    {
        std::cout << "\nERROR: Invalid Input.\n";
        actorMenu();
    }
    choice = answer[0];
    switch (choice) // navigate menu
    {
    case '1':
        std::cout << "\nPlease enter actor credentials.\n"; // prompt user to fill in actor info
        std::cout << "Enter actor name.\n";
        std::cin.ignore();
        std::getline(std::cin, answer);
        newrec.Name = answer;
        std::cout << "\nEnter year of nomination.\n";
        std::cin >> answer;
        newrec.Year = answer;
        std::cout << "\nEnter award name.\n";
        std::cin.ignore();
        std::getline(std::cin, answer);
        newrec.Award = answer;
        std::cout << "\nEnter if actor won award. 1 if yes. 0 if no.\n";
        std::cin >> answer;
        newrec.Winner = answer;
        std::cout << "\nEnter the film actor was nominated for.\n";
        std::cin.ignore();
        std::getline(std::cin, answer);
        newrec.Film = answer;
        std::cout << "\nEnter a ID not taken for the new record.\n" << "Max ID currently in tree: " << AD.max(AD.Root())->Key() << "\n";
        std::cin >> num;
        if (AD.contains(AD.Root(), num) || num == 0) // check if new ID is taken
        {
            std::cout << "\nID is taken.\n";
            actorMenu();
        }
        newrec.Label = num; // add new record to the tree and prompt user
        std::cout << "\nAdding... \n";
        newrec.printAct(std::cout);
        AD.addNode(newrec.Label, newrec);
        AD.setRoot(AD.buildBalancedTree(AD.Root()));
        std::cout << "\nRecord added...\n";
        actorMenu();
        break;
    case '2':
        std::cout << "\nPlease enter record ID to delete. If not press 0 to exit.\n"; // prompt user to input the unique record ID to delete it
        std::cin >> num;
        if (num == 0) { actorMenu(); }
        if (!AD.contains(AD.Root(), num) || num == 0) // check if ID exists
        {
            std::cout << "\nRecord not found.\n";
            actorMenu();
        }
        std::cout << "\nDeleting...\n";
        AD.findNode(num)->Data().printAct(std::cout);
        AD.deleteNode(num);                             // delete node/record
        AD.setRoot(AD.buildBalancedTree(AD.Root()));
        std::cout << "\nRecord deleted...\n";
        actorMenu();
        break;
    case '3':
        std::cout << "\nPlease enter record ID to modify. If not press 0 to exit.\n"; // prompt user to input the unique record ID to modify
        std::cin >> num;
        if (num == 0) { actorMenu(); }
        if (!AD.contains(AD.Root(), num) || num == 0) // check if record exists 
        {
            std::cout << "\nRecord not found.\n";
            actorMenu();
        }
        tmp = AD.findNode(num)->Data(); // get the record and store to tmp to modify data
        tmp.printAct(std::cout);
        std::cout << "\nSelect what field to modify.\n"; // prompt user which field they would like to modify
        std::cout << "1. Modify name.\n";
        std::cout << "2. Modify Year.\n";
        std::cout << "3. Modify Award.\n";
        std::cout << "4. Modify winner.\n";
        std::cout << "5. Modify film.\n";
        std::cout << "6. Exit\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
        }
        choice = answer[0];
        switch (choice) // each case will modify a specific data field
        {
        case '1':
            std::cout << "\nEnter updated actors name.\n";
            std::cin.ignore();
            std::getline(std::cin, answer);
            std::cout << "\nModifying record...\n";
            tmp.printAct(std::cout);
            tmp.Name = answer;
            AD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printAct(std::cout);
            break;
        case '2':
            std::cout << "\nEnter updated year.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printAct(std::cout);
            tmp.Year = answer;
            AD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printAct(std::cout);
            break;
        case '3':
            std::cout << "\nEnter updated award.\n";
            std::cin.ignore();
            std::getline(std::cin, answer);
            std::cout << "\nModifying record...\n";
            tmp.printAct(std::cout);
            tmp.Award = answer;
            AD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printAct(std::cout);
            actorMenu();
            break;
        case '4':
            std::cout << "\nEnter the updated actor award winner. 1 if yes. 0 if no.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printAct(std::cout);
            tmp.Winner = answer;
            AD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printAct(std::cout);
            actorMenu();
            break;
        case '5':
            std::cout << "\nEnter updated movie.\n";
            std::cin.ignore();
            std::getline(std::cin, answer);
            std::cout << "\nModifying record...\n";
            tmp.printAct(std::cout);
            tmp.Film = answer;
            AD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printAct(std::cout);
            actorMenu();
            break;
        case '6':
            actorMenu();
            break;
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
            break;
        }
        actorMenu();
        break;
    case '4':
        std::cout << "\nwhich search type would you like to do?\n"; // prompt user which kind of search they would like to do
        std::cout << "1. Exact search.\n";
        std::cout << "2. Partital search.\n";
        std::cout << "3. Exit.\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
        }
        choice = answer[0];
        switch (choice)
        {
        case '1': // each case will prompt the user to enter the field they would like to search and it will pull up every record based on the type of search
            std::cout << "\nwhich search field would you like to do?\n";
            std::cout << "1. Search by name.\n";
            std::cout << "2. Search by Year.\n";
            std::cout << "3. Search by Award.\n";
            std::cout << "4. Search by winner.\n";
            std::cout << "5. Search by film.\n";
            std::cout << "6. Search by ID.\n";
            std::cout << "7. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
            }
            choice = answer[0];
            switch (choice)
            {
            case '1':
                std::cout << "\nEnter the actors name.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 0, answer, true);
                actorMenu();
                break;
            case '2':
                std::cout << "\nEnter a year.\n";
                std::cin >> answer;
                AD.actorSearch(AD.Root(), 1, answer, true);
                actorMenu();
                break;
            case '3':
                std::cout << "\nEnter the name of award.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 2, answer, true);
                actorMenu();
                break;
            case '4':
                std::cout << "\nEnter if the actor won the award. 1 if yes. 0 if no.\n";
                std::cin >> answer;
                AD.actorSearch(AD.Root(), 3, answer, true);
                actorMenu();
                break;
            case '5':
                std::cout << "\nEnter a movie to search.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 4, answer, true);
                actorMenu();
                break;
            case '6':
                std::cout << "\nEnter a ID to search.\n";
                std::cin >> num;
                if (!AD.contains(AD.Root(), num))
                {
                    std::cout << "\nID not found.\n";
                    actorMenu();
                }
                AD.findNode(num)->Data().printAct(std::cout);
                actorMenu();
                break;
            case '7':

            default:
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
                break;
            }
            break;
        case '2':
            std::cout << "\nwhich search field would you like to do?\n";
            std::cout << "1. Search by name.\n";
            std::cout << "2. Search by Year.\n";
            std::cout << "3. Search by Award.\n";
            std::cout << "4. Search by winner.\n";
            std::cout << "5. Search by film.\n";
            std::cout << "6. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
            }
            choice = answer[0];
            switch (choice)
            {
            case '1':
                std::cout << "\nEnter the actors name.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 0, answer, false);
                actorMenu();
                break;
            case '2':
                std::cout << "\nEnter a year.\n";
                std::cin >> answer;
                AD.actorSearch(AD.Root(), 1, answer, false);
                actorMenu();
                break;
            case '3':
                std::cout << "\nEnter the name of award.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 2, answer, false);
                actorMenu();
                break;
            case '4':
                std::cout << "\nEnter if the actor won the award. 1 if yes. 0 if no.\n";
                std::cin >> answer;
                AD.actorSearch(AD.Root(), 3, answer, false);
                actorMenu();
                break;
            case '5':
                std::cout << "\nEnter a movie to search.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                AD.actorSearch(AD.Root(), 4, answer, false);
                actorMenu();
                break;
            case '6':
                actorMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
                break;
            }
            break;
        case '3':
            actorMenu();
            break;
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
            break;
        }
        break;
    case '5':
        std::cout << "\nwhich print type would you like to do?\n"; // prompt user if they wish to print database to screen or print it onto a new file in csv format
        std::cout << "1. Print to screen.\n";
        std::cout << "2. Print to file.\n";
        std::cout << "3. Exit.\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
        }
        choice = answer[0];
        switch (choice)
        {
        case '1': // prompt user to enter the sort filter to print the data and print to screen
            list.clear();
            AD.nodesDataVec(list, AD.Root());
            std::cout << "\nSelect what filter to print.\n"; // prompt user what to sort by and print to screen
            std::cout << "1. Print by name.\n";
            std::cout << "2. Print by Year.\n";
            std::cout << "3. Print by Award.\n";
            std::cout << "4. Print by winner.\n";
            std::cout << "5. Print by film.\n";
            std::cout << "6. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
            }
            choice = answer[0];
            switch (choice) // print to screen by looping through vector  and passing cout stream
            {
            case '1':
                sortActorVector(list, 0);
                for (actorRec entry : list)
                {
                    entry.printAct(std::cout);
                }
                actorMenu();
                break;
            case '2':
                sortActorVector(list, 1);
                for (actorRec entry : list)
                {
                    entry.printAct(std::cout);
                }
                actorMenu();
                break;
            case '3':
                sortActorVector(list, 2);
                for (actorRec entry : list)
                {
                    entry.printAct(std::cout);
                }
                actorMenu();
                break;
            case '4':
                sortActorVector(list, 3);
                for (actorRec entry : list)
                {
                    entry.printAct(std::cout);
                }
                actorMenu();
                break;
            case '5':
                sortActorVector(list, 4);
                for (actorRec entry : list)
                {
                    entry.printAct(std::cout);
                }
                actorMenu();
                break;
            case '6':
                actorMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
                break;
            }
            break;
        case '2': // prompt user to enter a file to write onto and the sort filter to write the data to the screen
            std::cout << "\nEnter file: ";
            std::cin >> answer;
            file.open(answer, std::ios::out | std::ios::trunc); // clear the the file to have a fresh empty file to write on 
            if (!file)
            {
                std::cout << "\nERROR: Could not open file. Back to menu...\n\n";
                actorMenu();
            }
            list.clear();
            AD.nodesDataVec(list, AD.Root());
            std::cout << "\nSelect what filter to print.\n"; // prompt user what to sort by and print to file
            std::cout << "1. Print by name.\n";
            std::cout << "2. Print by Year.\n";
            std::cout << "3. Print by Award.\n";
            std::cout << "4. Print by winner.\n";
            std::cout << "5. Print by film.\n";
            std::cout << "6. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
            }
            choice = answer[0];
            switch (choice) // print to file by looping through vector passing stream
            {
            case '1':
                sortActorVector(list, 0);
                file << "Year,Award,Winner,Name,Film\n";
                for (actorRec entry : list)
                {
                    entry.printActFile(file);
                }
                file.close();
                actorMenu();
                break;
            case '2':
                sortActorVector(list, 1);
                file << "Year,Award,Winner,Name,Film\n";
                for (actorRec entry : list)
                {
                    entry.printActFile(file);
                }
                file.close();
                actorMenu();
                break;
            case '3':
                sortActorVector(list, 2);
                file << "Year,Award,Winner,Name,Film\n";
                for (actorRec entry : list)
                {
                    entry.printActFile(file);
                }
                file.close();
                actorMenu();
                break;
            case '4':
                sortActorVector(list, 3);
                file << "Year,Award,Winner,Name,Film\n";
                for (actorRec entry : list)
                {
                    entry.printActFile(file);
                }
                file.close();
                actorMenu();
                break;
            case '5':
                sortActorVector(list, 4);
                file << "Year,Award,Winner,Name,Film\n";
                for (actorRec entry : list)
                {
                    entry.printActFile(file);
                }
                file.close();
                actorMenu();
                break;
            case '6':
                file.close();
                actorMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                file.close();
                actorMenu();
                break;
            }
            break;
        case '3':
            actorMenu();
            break;
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            actorMenu();
            break;
        }
        break;
    case '6':
        mainMenu(); // go to main menu
        break;
    case '7':
        std::cout << "\nExiting program...\n";
        exit(0); // leave program
        break;
    default:
        std::cout << "\nERROR: Invalid Input.\n";
        actorMenu();
        break;
    }
}

void movieMenu()
{
    ofstream out; // stream to write on file
    movieRec newrec, tmp; // tmp datatypes to manipulate records
    std::vector <movieRec> list; // vector to store aand sort data for printing
    std::string answer; // string to store user response
    char choice; // char to store user navigation through menus
    int num = 0; // integer for user to input ID
    std::cout << "\nMovie Datadabase Menu:\n" << "Choose option (1-7).\n"; // prompt user choices for navigation
    std::cout << "1. Add new record.\n";
    std::cout << "2. Delete record.\n";
    std::cout << "3. Modify record.\n";
    std::cout << "4. Search record.\n";
    std::cout << "5. Print records.\n";
    std::cout << "6. Exit to main menu.\n";
    std::cout << "7. Exit program\n";
    std::cin >> answer;
    if (answer.length() > 1)
    {
        std::cout << "\nERROR: Invalid Input.\n";
        movieMenu();
    }
    choice = answer[0];
    switch (choice)
    {
    case '1':
        std::cout << "\nPlease enter actor credentials. If credential unknown leave empty or type "-"\n"; // prompt user to enter movie credentials
        std::cout << "Enter film name.\n";
        std::cin.ignore();
        std::getline(std::cin, answer);
        newrec.Name = answer;
        std::cout << "\nEnter year of nomination.\n";
        std::cin >> answer;
        newrec.Year = answer;
        std::cout << "\nEnter the number of nominations of the film.\n";
        std::cin >> answer;
        newrec.Nominations = answer;
        std::cout << "\nEnter the movie rating of the movie.\n";
        std::cin >> answer;
        newrec.Rating = answer;
        std::cout << "\nEnter the duration of the film.\n";
        std::cin >> answer;
        newrec.Duration = answer;
        std::cout << "\nEnter the main genre of film.\n";
        std::cin >> answer;
        newrec.Genre1 = answer;
        std::cout << "\nEnter the second genre of film if applicable.\n";
        std::cin >> answer;
        newrec.Genre2 = answer;
        std::cout << "\nEnter the month the film was released.\n";
        std::cin >> answer;
        newrec.Release = answer;
        std::cout << "\nEnter the films metecritic score.\n";
        std::cin >> answer;
        newrec.Metacritic = answer;
        std::cout << "Enter the synopsis of the film.\n";
        std::cin.ignore();
        std::getline(std::cin, answer);
        newrec.Synopsis = answer;
        std::cout << "\nEnter a ID not taken for the new record.\n" << "Max ID currently in tree: " << MD.max(MD.Root())->Key() << "\n";
        std::cin >> num;
        if (MD.contains(MD.Root(), num) || num == 0) // check if ID is taken
        {
            std::cout << "\nID is taken.\n";
            movieMenu();
        }
        newrec.Label = num;
        std::cout << "\nAdding... \n";
        newrec.printFilm(std::cout);
        MD.addNode(newrec.Label, newrec); // add new movie record to tree
        MD.setRoot(MD.buildBalancedTree(MD.Root()));
        std::cout << "\nRecord added...\n";
        movieMenu();
        break;
    case '2':
        std::cout << "\nPlease enter record ID to delete. If not press 0 to exit.\n"; // prompt user to enter movie ID to delete
        std::cin >> num;
        if (num == 0) { movieMenu(); }
        if (!MD.contains(MD.Root(), num) || num == 0) // check if ID exists 
        {
            std::cout << "\nRecord not found.\n";
            movieMenu();
        }
        std::cout << "\nDeleting...\n";
        MD.findNode(num)->Data().printFilm(std::cout);
        MD.deleteNode(num);                             // delete ID
        MD.setRoot(MD.buildBalancedTree(MD.Root()));
        std::cout << "\nRecord deleted...\n";
        movieMenu();
        break;
    case '3':
        std::cout << "\nPlease enter record ID to modify. If not press 0 to exit.\n"; // prompt user to enter ID to modify
        std::cin >> num;
        if (num == 0) { movieMenu(); }
        if (!MD.contains(MD.Root(), num) || num == 0) // check if ID exists
        {
            std::cout << "\nRecord not found.\n";
            movieMenu();
        }
        tmp = MD.findNode(num)->Data(); // tmp to store current data to modify
        tmp.printFilm(std::cout);
        std::cout << "\nSelect what field to modify.\n"; // prompt user what field to modify
        std::cout << "1. Modify name.\n";
        std::cout << "2. Modify Year.\n";
        std::cout << "3. Modify amount of nominations.\n";
        std::cout << "4. Modify rating.\n";
        std::cout << "5. Modify film duration.\n";
        std::cout << "6. Modify genre.\n";
        std::cout << "7. Modify release month.\n";
        std::cout << "8. Modify metacrtitic score.\n";
        std::cout << "9. Modify film synopsis.\n";
        std::cout << "0. Exit\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
        }
        choice = answer[0];
        switch (choice) // modify selected field 
        {
        case '1':
            std::cout << "\nEnter updated film name.\n";
            std::cin.ignore();
            std::getline(std::cin, answer);
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Name = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '2':
            std::cout << "\nEnter updated year.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Year = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '3':
            std::cout << "\nEnter updated amount of nominations.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Nominations = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '4':
            std::cout << "\nEnter the updated film rating.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Rating = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '5':
            std::cout << "\nEnter updated film duration. (minutes).\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Duration = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '6':
            std::cout << "\nEnter updated genre.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Genre1 = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\nEnter updated second genre if applicable.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Genre2 = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '7':
            std::cout << "\nEnter updated release month.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Release = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
        case '8':
            std::cout << "\nEnter updated metacritic score.\n";
            std::cin >> answer;
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Metacritic = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '9':
            std::cout << "\nEnter updated film synopsis\n";
            std::cin.ignore();
            std::getline(std::cin, answer);
            std::cout << "\nModifying record...\n";
            tmp.printFilm(std::cout);
            tmp.Synopsis = answer;
            MD.findNode(num)->setData(tmp);
            std::cout << "\n\nModified record...\n";
            tmp.printFilm(std::cout);
            movieMenu();
            break;
        case '0':
            movieMenu();
            break;
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
            break;
        }
        movieMenu();
        break;
    case '4':
        std::cout << "\nwhich search type would you like to do?\n"; // prompt user what kind of search they would like to do
        std::cout << "1. Exact search.\n";
        std::cout << "2. Partital search.\n";
        std::cout << "3. Exit.\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
        }
        choice = answer[0];
        switch (choice)
        {
        case '1':
            std::cout << "\nwhich search field would you like to do?\n"; // prompt user what field to search
            std::cout << "1. Search by name.\n";
            std::cout << "2. Search by Year.\n";
            std::cout << "3. Search by amount of nominations.\n";
            std::cout << "4. Search by rating.\n";
            std::cout << "5. Search by film duration.\n";
            std::cout << "6. Search by genre.\n";
            std::cout << "7. Search by release month.\n";
            std::cout << "8. Search by metacrtitic score.\n";
            std::cout << "9. Search by ID.\n";
            std::cout << "0. Exit\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
            }
            choice = answer[0];
            switch (choice)
            {
            case '1': // complete search selected field
                std::cout << "\nEnter a film name.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                MD.movieSearch(MD.Root(), 0, answer, true);
                movieMenu();
                break;
            case '2':
                std::cout << "\nEnter a year.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 1, answer, true);
                movieMenu();
                break;
            case '3':
                std::cout << "\nEnter an amount of nominations.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 2, answer, true);
                movieMenu();
                break;
            case '4':
                std::cout << "\nEnter a film rating. (1-10).\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 3, answer, true);
                movieMenu();
                break;
            case '5':
                std::cout << "\nEnter a film duration. (minutes).\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 4, answer, true);
                movieMenu();
                break;
            case '6':
                std::cout << "\nEnter a genre.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 5, answer, true);
                movieMenu();
                break;
            case '7':
                std::cout << "\nEnter a release month.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 6, answer, true);
                movieMenu();
            case '8':
                std::cout << "\nEnter updated metacritic score. (0-100)\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 7, answer, true);
                movieMenu();
                break;
            case '9':
                std::cout << "\nEnter a ID to search.\n";
                std::cin >> num;
                if (!MD.contains(MD.Root(), num))
                {
                    std::cout << "\nID not found.\n";
                    movieMenu();
                }
                MD.findNode(num)->Data().printFilm(std::cout);
                movieMenu();
                break;
            case '0':
                movieMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
                break;
            }
            break;
        case '2':
            std::cout << "\nwhich search field would you like to do?\n"; // prompt user what field to search
            std::cout << "1. Search by name.\n";
            std::cout << "2. Search by Year.\n";
            std::cout << "3. Search by amount of nominations.\n";
            std::cout << "4. Search by rating.\n";
            std::cout << "5. Search by film duration.\n";
            std::cout << "6. Search by genre.\n";
            std::cout << "7. Search by release month.\n";
            std::cout << "8. Search by metacrtitic score.\n";
            std::cout << "9. Search by film synopsis.\n";
            std::cout << "0. Exit\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
            }
            choice = answer[0];
            switch (choice)
            {
            case '1': // partial search selected field
                std::cout << "\nEnter a film name.\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                MD.movieSearch(MD.Root(), 0, answer, false);
                movieMenu();
                break;
            case '2':
                std::cout << "\nEnter a year.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 1, answer, false);
                movieMenu();
                break;
            case '3':
                std::cout << "\nEnter an amount of nominations.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 2, answer, false);
                movieMenu();
                break;
            case '4':
                std::cout << "\nEnter a film rating. (1-10).\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 3, answer, false);
                movieMenu();
                break;
            case '5':
                std::cout << "\nEnter a film duration. (minutes).\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 4, answer, false);
                movieMenu();
                break;
            case '6':
                std::cout << "\nEnter a genre.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 5, answer, false);
                movieMenu();
                break;
            case '7':
                std::cout << "\nEnter a release month.\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 6, answer, false);
                movieMenu();
            case '8':
                std::cout << "\nEnter updated metacritic score. (0-100)\n";
                std::cin >> answer;
                MD.movieSearch(MD.Root(), 7, answer, false);
                movieMenu();
                break;
            case '9':
                std::cout << "\nEnter a film synopsis\n";
                std::cin.ignore();
                std::getline(std::cin, answer);
                MD.movieSearch(MD.Root(), 8, answer, false);
                movieMenu();
                break;
            case '0':
                movieMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
                break;
            }
            break;
        case '3':
            movieMenu();
            break;
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
            break;
        }
        break;
    case '5':
        std::cout << "\nwhich print type would you like to do?\n"; // prompt user to enter what where to print  database
        std::cout << "1. Print to screen.\n";
        std::cout << "2. Print to file.\n";
        std::cout << "3. Exit.\n";
        std::cin >> answer;
        if (answer.length() > 1)
        {
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
        }
        choice = answer[0];
        switch (choice)
        {
        case '1':
            list.clear();
            MD.nodesDataVec(list, MD.Root());
            std::cout << "\nSelect what filter to print.\n"; // prompt user what field to sort by and print to screen
            std::cout << "1. Print by name.\n";
            std::cout << "2. Print by Year.\n";
            std::cout << "3. Print by amount of nominations.\n";
            std::cout << "4. Print by rating.\n";
            std::cout << "5. Print by duration.\n";
            std::cout << "6. Print by genre.";
            std::cout << "7. Print by realease.\n";
            std::cout << "8. Print by metacritic score.\n";
            std::cout << "9. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
            }
            choice = answer[0];
            switch (choice) // print to screen by looping through vector
            {
            case '1':
                sortMovieVector(list, 0);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '2':
                sortMovieVector(list, 1);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '3':
                sortMovieVector(list, 2);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '4':
                sortMovieVector(list, 3);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '5':
                sortMovieVector(list, 4);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '6':
                sortMovieVector(list, 5);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '7':
                sortMovieVector(list, 6);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '8':
                sortMovieVector(list, 7);
                for (movieRec entry : list)
                {
                    entry.printFilm(std::cout);
                }
                movieMenu();
                break;
            case '9':
                movieMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                actorMenu();
                break;
            }
            break;
        case '2':
            std::cout << "\nEnter file: ";
            std::cin >> answer;
            out.open(answer, std::ios::out | std::ios::trunc);
            if (!out)
            {
                std::cout << "\nERROR: Could not open file. Back to menu...\n\n";
                movieMenu();
            }
            list.clear();
            MD.nodesDataVec(list, MD.Root());
            std::cout << "\nSelect what filter to print.\n"; // prompt user what field to sort by and print to screen
            std::cout << "1. Print by name.\n";
            std::cout << "2. Print by Year.\n";
            std::cout << "3. Print by amount of nominations.\n";
            std::cout << "4. Print by rating.\n";
            std::cout << "5. Print by duration.\n";
            std::cout << "6. Print by genre.";
            std::cout << "7. Print by realease.\n";
            std::cout << "8. Print by metacritic score.\n";
            std::cout << "9. Exit.\n";
            std::cin >> answer;
            if (answer.length() > 1)
            {
                std::cout << "\nERROR: Invalid Input.\n";
                movieMenu();
            }
            choice = answer[0];
            switch (choice) // print to screen by looping through vector
            {
            case '1':
                sortMovieVector(list, 0);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '2':
                sortMovieVector(list, 1);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '3':
                sortMovieVector(list, 2);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '4':
                sortMovieVector(list, 3);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '5':
                sortMovieVector(list, 4);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '6':
                sortMovieVector(list, 5);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '7':
                sortMovieVector(list, 6);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '8':
                sortMovieVector(list, 7);
                out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
                for (movieRec entry : list)
                {
                    entry.printFilmFile(out);
                }
                out.close();
                movieMenu();
                break;
            case '9':
                out.close();
                movieMenu();
                break;
            default:
                std::cout << "\nERROR: Invalid Input.\n";
                out.close();
                actorMenu();
                break;
            }
            break;
        case '3':
            movieMenu();
        default:
            std::cout << "\nERROR: Invalid Input.\n";
            movieMenu();
            break;
        }
        break;
    case '6':
        mainMenu(); // go to main menu
        break;
    case '7':
        std::cout << "\nExiting program...\n";
        exit(0); // exit program
        break;
    default:
        std::cout << "\nERROR: Invalid Input.\n";
        movieMenu();
        break;
    }
}


