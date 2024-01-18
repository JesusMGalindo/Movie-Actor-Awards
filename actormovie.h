#ifndef ACTORMOVIE_H  
#define ACTORMOVIE_H   

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

struct actorRec
{
		std::string Award, Name, Film, Year, Winner;
		int Label = 0;
		bool isEmpty()
		{
			return (Year.empty() && Name.empty() && Film.empty() && Winner.empty() && Award.empty());
		}
		void printAct(std::ostream& theStream) // format for database menus
		{
			theStream  << "ID: " << Label << " | " << Year << " | " << Award << " | " << Winner << " | " << Name << " | " << Film << " \n";
		}
		void printActFile(std::ostream& stream) // format for file print
		{
			stream  << Year << "," << Award << "," << Winner << "," << Name << "," << Film << " \n";
		}
		//search functions for complete and partial search
		bool containsYear(const std::string ayear)
		{
			std::string w1 = this->Year;
			std::string w2 = ayear;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPYear(const std::string _year)
		{
			std::string w1 = this->Year;
			std::string w2 = _year;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsName(const std::string aname)
		{
			std::string w1 = this->Name;
			std::string w2 = aname;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPName(const std::string _name)
		{
			std::string w1 = this->Name;
			std::string w2 = _name;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsAward(const std::string aaward)
		{
			std::string w1 = this->Award;
			std::string w2 = aaward;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPAward(const std::string _award)
		{
			std::string w1 = this->Award;
			std::string w2 = _award;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsWinner(const std::string awinner)
		{
			std::string w1 = this->Winner;
			std::string w2 = awinner;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPWinner(const std::string _winner)
		{
			std::string w1 = this->Winner;
			std::string w2 = _winner;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsFilm(const std::string afilm)
		{
			std::string w1 = this->Film;
			std::string w2 = afilm;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2); 
		}
		bool containsPFilm(const std::string _film)
		{
			std::string w1 = this->Film;
			std::string w2 = _film;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		friend bool operator==(const actorRec& a, const actorRec& b)
		{
			return(a.Label == b.Label);
		}
};


struct movieRec
{
		std::string Name, Genre1, Genre2, Release, Synopsis, Year, Nominations, Duration, Metacritic, Rating;
		int Label = 0;
		bool isEmpty()
		{
			return (Year.empty() && Name.empty() && Genre1.empty() && Genre2.empty() && Release.empty() && Synopsis.empty() && Nominations.empty() && Metacritic.empty() && Duration.empty() && Rating.empty());
		}
		void printFilm(std::ostream& theStream) // format for database menus
		{
			theStream << "ID: " << Label << " | " << Name << " | " << Year << " | " << Nominations << " | " << Rating << " | " << Duration << " | " << Genre1 << " | " << Genre2 << " | " << Release << " | " << Metacritic << " | " << Synopsis << " \n";
		}
		void printFilmFile(std::ostream& stream) // format for file print
		{
			stream << Name << "," << Year << "," << Nominations << "," << Rating << "," << Duration << "," << Genre1 << "," << Genre2 << "," << Release << "," << Metacritic << "," << Synopsis << " \n";
		}
		//search functions for complete and partial search
		bool containsYear(const std::string ayear)
		{
			std::string w1 = this->Year;
			std::string w2 = ayear;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPYear(const std::string _year)
		{
			std::string w1 = this->Year;
			std::string w2 = _year;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsName(const std::string aname)
		{
			std::string w1 = this->Name;
			std::string w2 = aname;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPName(const std::string _name)
		{
			std::string w1 = this->Name;
			std::string w2 = _name;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsNom(const std::string anom)
		{
			std::string w1 = this->Nominations;
			std::string w2 = anom;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPNom(const std::string _nom)
		{
			std::string w1 = this->Nominations;
			std::string w2 = _nom;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsRating(const std::string arating)
		{
			std::string w1 = this->Rating;
			std::string w2 = arating;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPRating(const std::string _rating)
		{
			std::string w1 = this->Rating;
			std::string w2 = _rating;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsDuration(const std::string aduration)
		{
			std::string w1 = this->Duration;
			std::string w2 = aduration;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPDuration(const std::string _duration)
		{
			std::string w1 = this->Duration;
			std::string w2 = _duration;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsGenre(const std::string agenre)
		{
			std::string w0 = this->Genre2;
			std::string w1 = this->Genre1; 
			std::string w2 = agenre;
			transform(w0.begin(), w0.end(), w0.begin(), ::toupper);
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2 || w0 == w2);
		}
		bool containsPGenre(const std::string _genre)
		{
			std::string w0 = this->Genre2;
			std::string w1 = this->Genre1;
			std::string w2 = _genre;
			transform(w0.begin(), w0.end(), w0.begin(), ::toupper);
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos || w0.find(w2) != std::string::npos);
		}
		bool containsRelease(const std::string arelease)
		{
			std::string w1 = this->Release;
			std::string w2 = arelease;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPRelease(const std::string _release)
		{
			std::string w1 = this->Release;
			std::string w2 = _release;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsMeta(const std::string ameta)
		{
			std::string w1 = this->Metacritic;
			std::string w2 = ameta;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPMeta(const std::string _meta)
		{
			std::string w1 = this->Metacritic;
			std::string w2 = _meta;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
		bool containsSyn(const std::string asyn)
		{
			std::string w1 = this->Synopsis;
			std::string w2 = asyn;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1 == w2);
		}
		bool containsPSyn(const std::string _syn)
		{
			std::string w1 = this->Synopsis;
			std::string w2 = _syn;
			transform(w1.begin(), w1.end(), w1.begin(), ::toupper);
			transform(w2.begin(), w2.end(), w2.begin(), ::toupper);
			return(w1.find(w2) != std::string::npos);
		}
};

void sortActorVector(std::vector <actorRec>& list, int field);

void sortMovieVector(std::vector <movieRec>& list, int field);

void sortActorVector(std::vector <actorRec>& list, int field) // function to sort a vector of actor data specified through given field
{
	if (field == 0)
	{
		sort(list.begin(), list.end(), [](const actorRec& lhs, const actorRec& rhs)
			{
				return lhs.Name < rhs.Name;
			});
	}
	if (field == 1)
	{
		sort(list.begin(), list.end(), [](const actorRec& lhs, const actorRec& rhs)
			{
				return lhs.Year < rhs.Year;
			});
	}
	if (field == 2)
	{
		sort(list.begin(), list.end(), [](const actorRec& lhs, const actorRec& rhs)
			{
				return lhs.Award < rhs.Award;
			});
	}
	if (field == 3)
	{
		sort(list.begin(), list.end(), [](const actorRec& lhs, const actorRec& rhs)
			{
				return lhs.Winner < rhs.Winner;
			});
	}
	if (field == 4)
	{
		sort(list.begin(), list.end(), [](const actorRec& lhs, const actorRec& rhs)
			{
				return lhs.Film < rhs.Film;
			});
	}
}

void sortMovieVector(std::vector <movieRec>& list, int field) // function to sort a vector of movie data specified through given field
{
	if (field == 0)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Name < rhs.Name;
			});
	}
	if (field == 1)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Year < rhs.Year;
			});
	}
	if (field == 2)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Nominations < rhs.Nominations;
			});
	}
	if (field == 3)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Rating < rhs.Rating;
			});
	}
	if (field == 4)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Duration < rhs.Duration;
			});
	}
	if (field == 5)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Genre1 < rhs.Genre1;
			});
	}
	if (field == 6)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Release < rhs.Release;
			});
	}
	if (field == 7)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Metacritic < rhs.Metacritic;
			});
	}
	if (field == 8)
	{
		sort(list.begin(), list.end(), [](const movieRec& lhs, const movieRec& rhs)
			{
				return lhs.Synopsis < rhs.Synopsis;
			});
	}
}

#endif
