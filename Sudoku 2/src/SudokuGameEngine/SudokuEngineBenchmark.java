package SudokuGameEngine;

public class SudokuEngineBenchmark {

    public static void gameGenerationBenchmark(
            final int difficulty,
            final int iterationsPerLoop,
            final int loops) {
        SudokuSolver engine = new SudokuSolver(3);
        long start = System.currentTimeMillis();
        for (int i = 0; i < loops; ++i) {
            for (int j = 0; j < iterationsPerLoop; ++j) {
                engine.newGame(difficulty);
            }
            System.out.println(i);
        }
        long finish = System.currentTimeMillis();
        System.out.println("Done in " + (finish - start) + " miliseconds!");
    }

    public static void gameSolvingBenchmark(
            final int difficulty,
            final int iterationsPerLoop,
            final int loops) {
        SudokuSolver engine = new SudokuSolver(3);
        int task[][] = new int[9][9];
        long executionTime = 0;
        for (int loop = 0; loop < loops; ++loop) {
            engine.newGame(difficulty);
            try {
                for (int i = 0; i < 9; ++i) {
                    for (int j = 0; j < 9; ++j) {
                        task[i][j] = engine.isFilled(i + 1, j + 1) ? engine.get(i + 1, j + 1) : 0;
                    }
                }
            } catch (BadIndex bi) {
                System.err.println("Bad index " + bi);
            }
            long start = System.currentTimeMillis();
            for (int iteration = 0; iteration < iterationsPerLoop; ++iteration) {
                try {
                    engine.solveTask(task);
                } catch (BadIndex bi) {
                    System.err.println("Bad index " + bi);
                }
            }
            long finish = System.currentTimeMillis();
            executionTime += finish - start;
            System.out.println(loop);
        }

        System.out.println("Done in " + executionTime + " miliseconds!");
    }

    public static void main(String args[]) {
        gameGenerationBenchmark(4, 10, 10);
        gameSolvingBenchmark(4, 100, 100);
    }
}
