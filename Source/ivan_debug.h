#ifndef IVAN_DEBUG_H
#define IVAN_DEBUG_H

#define TIMED_BLOCK__(Number, ...) timed_block TimedBlock_##Number(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__)
#define TIMED_BLOCK_(Number, ...) TIMED_BLOCK__(Number, ## __VA_ARGS__)
#define TIMED_BLOCK(...) TIMED_BLOCK_(__LINE__, ## __VA_ARGS__)

struct debug_record{
	char* FileName;
	char* FunctionName;

	uint32 LineNumber;

	uint64 HitCount_CycleCount;
};

debug_record DebugRecordArray[];

struct timed_block{
	debug_record* Record;
	uint64 StartCycles;
	uint32 HitCount;

	timed_block(int Counter, char* FileName, int LineNumber, char* FunctionName, uint32 HitCountInit = 1)
	{
		HitCount = HitCountInit;
		
		Record = DebugRecordArray + Counter;
		Record->FileName = FileName;
		Record->LineNumber = LineNumber;
		Record->FunctionName = FunctionName;

		StartCycles = __rdtsc();
	}

	~timed_block(){
		uint64 Delta = (__rdtsc() - StartCycles) | ((uint64)HitCount << 32);
		AtomicAddU64(&Record->HitCount_CycleCount, Delta);
	}
};

#endif