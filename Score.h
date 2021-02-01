#ifndef SCORE_H
#define SCORE_H
#include <cstring>
#include <algorithm>


class Score {
public:
	int get_score(){ return score;}
	std::string get_name(){ return name;}
	void set_score(int x){ score = x; }
	void set_name(std::string s){ std::strcpy( name , s.c_str() ); }
	void sort_scores( std::vector<Score> &v_sc )
	{	
			std::sort( v_sc.begin() , v_sc.end() );
					std::reverse(v_sc.begin() , v_sc.end() );
	}
	
	bool operator<(const Score &sc) const
	{
			if(score < sc.score)
				return true;
			else
				return false;
	}
	
	bool operator> (const Score &sc)const
	{
		if ( score > sc.score )
			return true;
		else
			return false;
	}
	
private:
	int score;
	char name[13];
	
};

#endif

