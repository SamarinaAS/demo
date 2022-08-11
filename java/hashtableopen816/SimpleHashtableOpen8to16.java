package com.epam.rd.autocode.hashtableopen816;

public class SimpleHashtableOpen8to16 implements HashtableOpen8to16 {
    private final static int MAXIMUM_CAPACITY = 16;
    private final static int INITIAL_CAPACITY = 8;
    private int numberOfElements;
    private int capacity;
    private Integer[] keysInteger;
    private Object[] values;

    public SimpleHashtableOpen8to16() {
        this.capacity = INITIAL_CAPACITY;
        this.keysInteger = new Integer[INITIAL_CAPACITY];
        this.values = new Object[INITIAL_CAPACITY];
    }

    private SimpleHashtableOpen8to16(int capacity) {
        this.capacity = capacity;
        this.keysInteger = new Integer[capacity];
        this.values = new Object[capacity];
    }

    private int hash(int key) {
        Integer keyInteger = key;
        if (key >= 0) {
            return keyInteger.hashCode() % capacity;
        } else {
            return capacity - keyInteger.hashCode() & (capacity - 1);
        }
    }

    private void resize(int capacity) {
        if (capacity > MAXIMUM_CAPACITY) {
            throw new IllegalStateException();
        }
        SimpleHashtableOpen8to16 hashTableWithNewSize = new SimpleHashtableOpen8to16(capacity);
        for (int i = 0; i < this.capacity; i++) {
            if (keysInteger[i] != null) {
                hashTableWithNewSize.insert(keysInteger[i], values[i]);
            }
        }
        this.keysInteger = hashTableWithNewSize.keysInteger;
        this.values = hashTableWithNewSize.values;
        this.capacity = hashTableWithNewSize.capacity;
    }

    @Override
    public void insert(int key, Object value) {
        Integer keyInteger = key;
        if (numberOfElements == capacity && search(key) == null) {
            resize(capacity * 2);
        }
        int i;
        for (i = hash(key); keysInteger[i] != null; i = (i + 1) % capacity) {
            if (keysInteger[i].equals(keyInteger)) {
                values[i] = value;
                return;
            }
        }
        keysInteger[i] = keyInteger;
        values[i] = value;
        numberOfElements++;
    }

    @Override
    public Object search(int key) {
        Integer keyInteger = key;
        int counter = 0;
        while (counter != capacity) {
            if (keysInteger[counter] != null && keysInteger[counter].equals(keyInteger)) {
                return values[counter];
            }
            counter++;
        }
        return null;
    }

    @Override
    public void remove(int key) {
        Integer keyInteger = key;
        if (search(key) == null) {
            return;
        }
        int i = hash(key);
        while (!keyInteger.equals(keysInteger[i])) {
            i = (i + 1) % capacity;
        }
        keysInteger[i] = null;
        values[i] = null;
        numberOfElements--;
        if (numberOfElements <= capacity / 4 && capacity / 2 >= 2) {
            resize(capacity / 2);
        }

    }

    @Override
    public int size() {
        return capacity;
    }

    @Override
    public int[] keys() {
        int[] keys = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            if (keysInteger[i] == null) {
                keys[i] = 0;
            } else {
                keys[i] = keysInteger[i];
            }
        }
        return keys;
    }
}
