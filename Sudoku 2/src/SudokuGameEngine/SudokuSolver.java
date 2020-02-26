package SudokuGameEngine;

import java.io.Serializable;

public class SudokuSolver implements Serializable {

    private final int blockSize;
    private final int fieldSize;
    private SudokuField field;
    private int solutions;

    public SudokuSolver(final int sizeOfBlock) {
        blockSize = sizeOfBlock;
        fieldSize = blockSize * blockSize;
        field = new SudokuField(blockSize);
        solutions = 0;
    }

    public int numberOfCells() {
        return field.numberOfCells();
    }

    public int numberOfFilledCells() {
        return field.numberOfFilledCells();
    }

    public int numberOfHiddenCells() {
        return field.numberOfHiddenCells();
    }

    public boolean isFilled(final int i, final int j) throws BadIndex {
        if (i < 1 || i > fieldSize || j < 1 || j > fieldSize) {
            throw new BadIndex(i, j);
        }
        return field.isFilled(i, j);
    }

    public int get(final int i, final int j) throws BadIndex {
        if (i < 1 || i > fieldSize || j < 1 || j > fieldSize) {
            throw new BadIndex(i, j);
        }
        return field.get(i, j);
    }

    public int solutions() {
        return solutions;
    }

    public void newGame(final int difficulty) {
        field.resetAllCells();
        generateFullField(1, 1);
        switch (difficulty) {
            case 0:
                hideCells(39 * fieldSize * fieldSize / 100);
                break;
            case 1:
                hideCells(48 * fieldSize * fieldSize / 100);
                break;
            case 2:
                hideCells(56 * fieldSize * fieldSize / 100);
                break;
            case 3:
                hideCells(65 * fieldSize * fieldSize / 100);
                break;
            case 4:
                hideAsManyCellsAsPossible();
                break;
            default:
                hideCells((blockSize <= 3 ? 56 : 35) * fieldSize * fieldSize / 100);
                break;
        }
    }

    public void solveTask(int[][] task) throws BadIndex {
        if (task.length != fieldSize) {
            throw new BadIndex(task.length, task.length);
        }
        for (int i = 0; i < fieldSize; ++i) {
            if (task[i].length != fieldSize) {
                throw new BadIndex(task.length, task[i].length);
            }
        }
        field.resetAllCells();
        solutions = 0;
        for (int i = 1; i <= fieldSize; ++i) {
            for (int j = 1; j <= fieldSize; ++j) {
                if (task[i - 1][j - 1] >= 1 && task[i - 1][j - 1] <= fieldSize) {
                    field.set(task[i - 1][j - 1], i, j);
                } else if (task[i - 1][j - 1] == 0) {
                    field.hide(i, j);
                } else {
                    throw new BadIndex(i, j);
                }
            }
        }
        if (field.isCorrect()) {
            solveGame(true);
            if (solutions == 1) {
                solveGame(false);
                for (int i = 1; i <= fieldSize; ++i) {
                    for (int j = 1; j <= fieldSize; ++j) {
                        field.show(i, j);
                    }
                }
            }
        } else {
            solutions = 0;
        }
    }

    private void generateFullField(final int row, final int column) {
        if (!field.isFilled(field.fieldSize(), field.fieldSize())) {
            while (field.numberOfTriedNumbers(row, column) < field.variantsPerCell()) {
                int candidate = 0;
                do {
                    candidate = field.getRandomIndex();
                } while (field.numberHasBeenTried(candidate, row, column));
                if (field.checkNumberField(candidate, row, column)) {
                    field.set(candidate, row, column);
                    Index nextCell = field.nextCell(row, column);
                    if (nextCell.i <= field.fieldSize()
                            && nextCell.j <= field.fieldSize()) {
                        generateFullField(nextCell.i, nextCell.j);
                    }
                } else {
                    field.tryNumber(candidate, row, column);
                }
            }
            if (!field.isFilled(field.fieldSize(), field.fieldSize())) {
                field.reset(row, column);
            }
        }
    }

    private void solveGame(final boolean hideSolution) {
        solutions = 0;
        if (hideSolution) {
            countVariants();
        } else {
            solve();
        }
    }

    private void countVariants() {
        if (solutions > 1) {
            return;
        }
        if (field.allCellsFilled()) {
            ++solutions;
        } else {
            Index minCell = field.cellWithMinVariants();
            int previousValue = field.get(minCell.i, minCell.j);
            for (int i = 1; i <= fieldSize; ++i) {
                if (field.checkNumberField(i, minCell.i, minCell.j)) {
                    field.set(i, minCell.i, minCell.j);
                    countVariants();
                    if (previousValue >= 1 && previousValue <= fieldSize) {
                        field.set(previousValue, minCell.i, minCell.j);
                    } else {
                        field.reset(minCell.i, minCell.j);
                    }
                    field.hide(minCell.i, minCell.j);
                    if (solutions > 1) {
                        return;
                    }
                }
            }
        }
    }

    private void solve() {
        if (solutions > 1) {
            return;
        }
        if (field.allCellsFilled()) {
            ++solutions;
        } else {
            Index minCell = field.cellWithMinVariants();
            for (int i = 1; (i <= fieldSize && solutions == 0); ++i) {
                if (field.checkNumberField(i, minCell.i, minCell.j)) {
                    field.set(i, minCell.i, minCell.j);
                    solve();
                    if (solutions == 0) {
                        field.hide(minCell.i, minCell.j);
                    }
                }
            }
        }
    }

    private void hideCell(final int i, final int j) {
        if (field.isFilled(i, j)) {
            field.hide(i, j);
            solveGame(true);
            if (solutions > 1) {
                field.show(i, j);
            }
        }
    }

    private void hideCells(final int number) {
        int hidden = 0;
        while (hidden < number) {
            int row = field.getRandomIndex();
            int column = field.getRandomIndex();
            if (field.isFilled(row, column)) {
                field.hide(row, column);
                solveGame(true);
                if (solutions == 1) {
                    ++hidden;
                } else {
                    field.show(row, column);
                }
            }
        }
    }

    private void hideAsManyCellsAsPossible() {
        class CandidateSeeker {

            boolean seek(final boolean[][] cover, final int coverSize) {
                for (int i = 0; i < coverSize; ++i) {
                    for (int j = 0; j < coverSize; ++j) {
                        if (cover[i][j]) {
                            return true;
                        }
                    }
                }
                return false;
            }
        }

        boolean[][] cover = new boolean[fieldSize][fieldSize];
        for (int i = 0; i < fieldSize; ++i) {
            for (int j = 0; j < fieldSize; ++j) {
                cover[i][j] = true;
            }
        }
        CandidateSeeker seeker = new CandidateSeeker();
        while (seeker.seek(cover, fieldSize)) {
            int i = field.getRandomIndex();
            int j = field.getRandomIndex();
            hideCell(i, j);
            cover[i - 1][j - 1] = false;
        }
    }
}