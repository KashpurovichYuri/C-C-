#include <iostream>
#include <string>

enum class Report
{
	exam,
	difoffset,
	offset,
};

template <typename Derived>
class Subj
{
public:
	Derived* self()
	{
		return static_cast<Derived*> (this);
	}

	float SubjComplexity() const
	{
		float res = freebieImp() + reportImp() + qualityImp();
		if (res > 10)
			return 10.0;
		else if (res > 5)
			return 0.3 * freebieImp() + reportImp() + 0.7 * qualityImp();
		else
			return 0.7 * freebieImp() + reportImp() + 0.3 * qualityImp();
	}

protected:
	float amountImp() const
	{
		return amount;
	}

	float difficultyImp() const
	{
		return self()->difficultyImp();
	}

	float qualityImp() const
	{
		return self()->qualityImp();
	}

	float freebieImp() const
	{
		return freebie;
	}

	float reportImp() const
	{
		switch (report)
		{
			case Report::exam:
				return difficulty * 3;
			case Report::difoffset:
				return difficulty * 2;
			case Report::offset:
				return difficulty * 1;
			default:
				return 0;
		}
	}

	auto getDifficulty() const
	{
		return difficulty;
	}

	auto getQuality() const
	{
		return quality;
	}
	
private:
	int amount; 		// assignments' amount
	float difficulty; 	// assingments' difficulty
	float quality;  	// quality of execution tasks
	float freebie;  	// freebie of teacher
	Report report; 		// reporting form
};

class SubjMath: public Subj<SubjMath>
{
protected:
	auto attendanceImp() const
	{
		return static_cast<float> (attendance) / lessons;
	}

	auto activityImp() const
	{
		return activity;
	}

	float difficultyImp() const
	{
		return (getDifficulty() + attendanceImp()) / 2.0;
	}

	float qualityImp() const
	{
		return (getQuality() + activityImp()) / 2.0 * difficultyImp() * amountImp();
	}

private:
	const int lessons { 15 };
	int attendance; // number of classes attended
	bool activity;	// involving in work on seminar
};

class SubjProgramming: public Subj<SubjProgramming>
{
protected:
	auto frequencyImp() const
	{
		return frequency / semestr_time;
	}

	float difficultyImp() const
	{
		return (getDifficulty() + frequencyImp()) / 2.0;
	}

	float qualityImp() const
	{
		return getQuality() * difficultyImp() * amountImp();
	}

private:
	const int semestr_time { 15 }; 	// weeks at semestr
	int frequency;		// frequency of assignments' turning in by week
};

class SubjPhysics: public Subj<SubjPhysics>
{
protected:
	auto controlsImp() const
	{
		return controls * 1.5;
	}

	float difficultyImp() const
	{
		return (getDifficulty() + controlsImp()) / 2.0;
	}

	float qualityImp() const
	{
		return getQuality() * difficultyImp() * amountImp();
	}

private:
	int controls; // number of control events	
};

class SubjEnglish: public Subj<SubjEnglish>
{
protected:
	auto attendanceImp() const
	{
		return static_cast<float> (attendance * lessons) / (lessons * lessons) ;
	}

	auto activityImp() const
	{
		return (activity * attendance * 2) / (lessons * 2);
	}

	auto independenceImp() const
	{
		return independence;
	}

	float difficultyImp() const
	{
		return (getDifficulty() + attendanceImp()) / 2.0;
	}

	float qualityImp() const
	{
		return (getQuality() + independenceImp() + activityImp()) / 3.0 * difficultyImp() * amountImp();
	}

private:
	const int lessons { 30 };
	int attendance; // required number of classes attended
	bool activity;	// involving in work on seminar
	float independence; // independence of work
};

int main()
{
	
}

/*
	Differences and features of MixInMethod:
		В этой реализации нет виртуальных функций, но при этом также реализуется множественное наследование.
		Код стал короче (не нужно описывать чисто виртуальные функции в базовом классе).
		Основная реализация делается в базовом классе, а индивидуальную функциональность мы “подмешиваем” из производных классов. При этом могут использоваться не все функции родительского класса.
*/