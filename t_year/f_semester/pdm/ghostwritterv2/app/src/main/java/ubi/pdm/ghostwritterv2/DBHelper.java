package ubi.pdm.ghostwritterv2;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class DBHelper extends SQLiteOpenHelper {
    private static final String DB_NAME = "ghostwriter.db";
    private static final int DB_VERSION = 1;

    public DBHelper(Context ctx) {
        super(ctx, DB_NAME, null, DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE users (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                "name TEXT UNIQUE NOT NULL)");

        db.execSQL("CREATE TABLE sessions (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                "date_iso TEXT NOT NULL, " +
                "text_full TEXT, " +
                "text_path TEXT)");

        db.execSQL("CREATE TABLE session_users (" +
                "session_id INTEGER, " +
                "user_id INTEGER, " +
                "PRIMARY KEY (session_id, user_id), " +
                "FOREIGN KEY (session_id) REFERENCES sessions(id) ON DELETE CASCADE, " +
                "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE)");
    }

    public long insertUser(String name) {
        ContentValues cv = new ContentValues();
        cv.put("name", name.trim());
        return
                getWritableDatabase().insertWithOnConflict("users", null,
                        cv, SQLiteDatabase.CONFLICT_IGNORE);
    }

    public long getUserIdByName(String name) {
        long id = -1;
        Cursor c = getReadableDatabase().query(
                "users",
                new String[]{"id"},
                "name=?",
                new String[]{name.trim()},
                null, null, null
        );

        if (c.moveToFirst()) id = c.getLong(0);
        c.close();
        return id;
    }

    public List<String> getAllUserNames() {
        List<String> list = new ArrayList<>();
        Cursor c = getReadableDatabase().query(
                "users",
                new String[]{"name"},
                null, null, null, null,
                "name ASC"
        );
        while (c.moveToNext()) {
            list.add(c.getString(0));
        }
        c.close();
        return list;
    }

    public long insertSession(String dateIso, String textFull, String textPath) {
        ContentValues cv = new ContentValues();
        cv.put("date_iso", dateIso);
        cv.put("text_full", textFull);
        cv.put("text_path", textPath);
        return getWritableDatabase().insert("sessions", null, cv);
    }

    public void linkUsersToSession(long sessionId, List<String> userNames) {
        SQLiteDatabase db = getWritableDatabase();
        for (String name : userNames) {
            long uid = getUserIdByName(name);
            if (uid <= 0) uid = insertUser(name);
            ContentValues cv = new ContentValues();
            cv.put("session_id", sessionId);
            cv.put("user_id", uid);
            db.insertWithOnConflict("session_users", null, cv, SQLiteDatabase.CONFLICT_IGNORE);
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {  }
}
