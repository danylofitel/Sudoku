package SudokuGameEngine;

import java.io.Serializable;

public class BadIndex extends Throwable implements Serializable {

    public final int first, second;

    public BadIndex(final int i, final int j) {
        first = i;
        second = j;
    }
}