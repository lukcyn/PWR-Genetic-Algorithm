#include "ProbGenerator.h"
#include "Individual.h"
#include "KnapsackProblem.h"

RandomGenerator Individual::_boolGenerator(0, 1);

ProbGenerator* Individual::_probGenerator = ProbGenerator::GetInstance();

Individual::Individual(const size_t& genomeSize) 
	: _indexGenerator(0, genomeSize - 1)
{
	_genome = new bool[genomeSize];
	_genomeSize = genomeSize;

	_boolGenerator.SeedData(_genome, _genomeSize);
}

Individual::Individual(const Individual& other)
	: _indexGenerator(other._indexGenerator)
{
	_genomeSize = other._genomeSize;
	_genome = new bool[_genomeSize];


	for(int i=0; i<_genomeSize; ++i)
		_genome[i] = other._genome[i];
}

Individual& Individual::operator=(const Individual& other)
{
	if (&other == this)
		return *this;

	delete _genome;
	_genomeSize = other._genomeSize;
	_genome = new bool[other._genomeSize];

	for (int i = 0; i < _genomeSize; ++i)
		_genome[i] = other._genome[i];

	_indexGenerator = other._indexGenerator;
	
	return *this;
}

Individual::Individual(Individual&& other) noexcept
	:_indexGenerator(other._indexGenerator)
{
	_genome = other._genome;
	other._genome = NULL;

	_genomeSize = other._genomeSize;
}

Individual& Individual::operator&&(Individual&& other) noexcept
{
	if (&other == this)
		return *this;

	delete _genome;
	_genome = other._genome;
	_genomeSize = other._genomeSize;

	other._genome = NULL;

	return *this;
}

int Individual::CalculateFitness(KnapsackProblem& judge)
{
	return judge.CalculateFitness(_genome, _genomeSize);
}

Individual::~Individual()
{
	delete[] _genome;
}

void Individual::Mutate(const float& mutationProb)
{
	for (size_t i = 0; i < _genomeSize; ++i)
	{
		if (_probGenerator->NextValue() >= mutationProb)
		{
			_genome[i] = !_genome[i];
		}
	}
}

std::pair<Individual, Individual> Individual::Cross(const Individual& other) const
{
	//TODO: change to scheme theory...
	Individual i1(_genomeSize);
	Individual i2(_genomeSize);

	bool* genome1 = i1._genome;
	bool* genome2 = i2._genome;

	for (size_t i = 0; i < _genomeSize; ++i)
	{
		if (_boolGenerator.NextValue())
		{
			*genome1 = _genome[i];
			*genome2 = other._genome[i];
		}
		else
		{
			*genome1 = other._genome[i];
			*genome2 = _genome[i];
		}
		++genome1;
		++genome2;
	}


	return std::make_pair(i1, i2);
}