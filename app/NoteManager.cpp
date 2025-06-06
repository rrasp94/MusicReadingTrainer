#include "NoteManager.h"



namespace MusicReadingTrainer {

    void NoteManager::addNote(const Note& note) {

        notes.push_back(note);

    }

    void NoteManager::updateNotes() {
        
        for (auto& note : notes) {
            --note.x;
        }
    }

    void NoteManager::removeOffscreenNotes() {

        notes.erase(
            std::remove_if(notes.begin(), notes.end(), [](const Note& note) {
                return note.x <= 11;
                }),
            notes.end()
        );

    }

    const std::vector<Note>& NoteManager::getNotes() const {

        return notes;

    }

    std::vector<Note>& NoteManager::getNotes() {

        return notes;

    }


    void NoteManager::drawNotes(ScreenBuffer& screen) {
        for (const Note& note : notes) {
            int x = note.x;
            int y = note.y;
            wchar_t symbol = note.getSymbol();

            
            screen.setCharAt(x, y, symbol);

            
            if (y == 4 || y == 16) {
                // -O-
                screen.setCharAt(x - 1, y, L'-');
                screen.setCharAt(x + 1, y, L'-');
                screen.setCharAt(x - 2, y, L'-');
                screen.setCharAt(x + 2, y, L'-');
            }
            else if (y == 3) {
                //  O
                // ---
                screen.setCharAt(x, y, symbol);
                screen.setCharAt(x - 1, y + 1, L'-');
                screen.setCharAt(x, y + 1, L'-');
                screen.setCharAt(x + 1, y + 1, L'-');
                screen.setCharAt(x + 2, y + 1, L'-');
                screen.setCharAt(x -2, y + 1, L'-');
            }
            else if (y == 17) {
                // ---
                //  O
                screen.setCharAt(x - 1, y - 1, L'-');
                screen.setCharAt(x, y - 1, L'-');
                screen.setCharAt(x + 1, y - 1, L'-');
                screen.setCharAt(x + 2, y - 1, L'-');
                screen.setCharAt(x - 2, y - 1, L'-');
            }
            else if (y == 2) {
                // -O-
                // ---
                screen.setCharAt(x - 1, y, L'-');
                screen.setCharAt(x + 1, y, L'-');
                screen.setCharAt(x + 2, y, L'-');
                screen.setCharAt(x - 2, y, L'-');

                screen.setCharAt(x - 1, y + 2, L'-');
                screen.setCharAt(x, y + 2, L'-');
                screen.setCharAt(x + 1, y + 2, L'-');
                screen.setCharAt(x + 2, y + 2, L'-');
                screen.setCharAt(x - 2, y + 2, L'-');
            }
            else if (y == 18) {
                // ---
                // -O-
                screen.setCharAt(x - 1, y - 2, L'-');
                screen.setCharAt(x, y - 2, L'-');
                screen.setCharAt(x + 1, y - 2, L'-');
                screen.setCharAt(x + 2, y - 2, L'-');
                screen.setCharAt(x - 2, y - 2, L'-');


                screen.setCharAt(x - 1, y, L'-');
                screen.setCharAt(x + 1, y, L'-');
                screen.setCharAt(x + 2, y, L'-');
                screen.setCharAt(x - 2, y, L'-');
            }
        }
    }

    bool NoteManager::shouldGenerateNewNote(int distance) const {
        if (notes.empty()) return true;

        const Note& lastNote = notes.back();
        return (115 - lastNote.x) >= distance;
    }

    int NoteManager::getFirstActiveNoteIndex() const {

        for (int i = 0; i < (int)notes.size(); ++i) {
            if (!notes[i].wasProcessed)
                return i;
        }
        return -1;
    }

    void NoteManager::drawArrowAboveActiveNote(ScreenBuffer& screen) const {
        for (const auto& note : notes) {
            if (note.status == NoteStatus::Untouched && note.x > 24) {
                int arrowX = note.x;
                int arrowY = note.y;

                if (arrowY - 1 >= 0 && arrowX >= 0 && arrowX < screen.getWidth()) {
                    screen.setCharAt(arrowX, arrowY - 1, L'v');
                }

                break;
            }
        }
    }

    void NoteManager::clearNotes() {
        notes.clear();
    }

}