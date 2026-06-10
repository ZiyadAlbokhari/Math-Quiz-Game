#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedyLevel = 2, HardyLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

int ReadHowManyQuestions()
{
	int NumberOfQuestions = 0;

	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;

	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

enOperationType GetRandomOpType()
{
	int OpType = RandomNumber(1, 4);

	return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenarateQuestions(enQuestionsLevel QuestionsLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOpType();
	}

	Question.OperationType = OpType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::MedyLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::HardyLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionsLevel = QuestionsLevel;
		return Question;
	}

	return Question;
}

void GenarateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenarateQuestions(Quizz.QuestionsLevel, Quizz.OperationType);
	}
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n-----------" << endl;
}

int ReadQuestionAnswer()
{
	int Answer = 0;

	cin >> Answer;

	return Answer;
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}

	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-(\n";
	}

	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}

string GetQuestionsLevelText(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionsLevelText[4] = { "Easy", "Med", "Hard", "Mix" };

	return arrQuestionsLevelText[QuestionsLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass) << endl;
	cout << "______________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";

	SetScreenColor(Quizz.isPass);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OperationType = ReadOperationType();

	GenarateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}