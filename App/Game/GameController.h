//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_GAMECONTROLLER_H
#define UNTITLED_GAMECONTROLLER_H

#include <GL/freeglut.h>
#include "../WebServices/OnlineGameController.h"
#include "GameModel.h"
#include "GameViewer.h"

#include "../WebServices/ConnectionManager.h"

#include "../GameElements/Board.h"


/**
 * @class GameController
 * @brief Controller for managing game interactions.
 *
 * The `GameController` class is responsible for managing user inputs and game logic
 * in the context of a game. It handles key presses, game state transitions, and communication
 * with an online opponent.
 */
class GameController : public SceneController {
public:
    /**
    * @brief Handle keyboard key presses.
    *
    * @param key The pressed key.
    * @param x The x-coordinate of the key press.
    * @param y The y-coordinate of the key press.
    */
    void handleKeyPress(unsigned char key, int x, int y) {
        if (key == 8) {
            gameModel->removeFromText();//text.pop_back();
        } else if (key == 13) {
            enterMove();
        } else {
            gameModel->clearMessage();
            gameModel->textAppend((char) toupper(key));
        }
    }

    /**
    * @brief Constructor for the `GameController` class.
    *
    * @param gameModelPtr Pointer to the associated `GameModel` object.
    */
    GameController(GameModel* gameModelPtr) {
        gameModel = gameModelPtr;
    }

    /**
        * @brief Create a new game.
        *
        * Initializes the online game controller, sets the opponent's turn, and starts the game.
        */
    void createGame() {
        onlineGameController = new OnlineGameController(new ConnectionManager, true);
        gameModel->setOpponentTurn();
        getOpponentMove();
    } /**
     * @brief Join an existing game.
     *
     * Initializes the online game controller for joining an existing game.
     */
    void joinGame() {
        onlineGameController = new OnlineGameController(new ConnectionManager, false);
    }

    /**
        * @brief Process the user's move input.
        *
        * Parses and validates the move input, then sends it to the opponent for processing.
        */
    void enterMove() {
        Coordinate coordinates = Coordinate(gameModel->getText());
        if (gameModel->isAttackMoveValid(coordinates)) {
            gameModel->clearText();
            Response response = onlineGameController->attack(coordinates);
            processAttackResponse(response, coordinates);
        } else {
            wrongMove();
        }
    } /**
     * @brief Process the response from an attack move.
     *
     * Updates the game state based on the response received from the opponent.
     *
     * @param response The response from the opponent.
     * @param coordinate The coordinate of the attack move.
     */
    void processAttackResponse(Response response, Coordinate coordinate) {
        if (response.type == ResponseType::RESULT) {
            if (gameModel->getTurn() == LOCAL_PLAYER) {
                AttackResult attackResult = mapStringToAttackResult(response.body);
                gameModel->processAttackResult(attackResult, coordinate);
                if (gameModel->getTurn() == OPPONENT) {
                    onlineGameController->postReadyForAnswering();
                    getOpponentMove();
                } else if (gameModel->getTurn() == END) {
                    gameModel->setMessage("GAME END");
                }
            }
        } else {
            processResponse(response);
        }
    } /**
     * @brief Get the opponent's move.
     *
     * Requests the opponent's move from the online game controller.
     */
    void getOpponentMove() {
        Response response = onlineGameController->getMove();
        processOpponentAttack(response);
    }

    /**
    * @brief Process the opponent's attack move.
    *
    * Updates the game state based on the opponent's attack move and sends the result back.
    *
    * @param response The response from the opponent.
    */
    void processOpponentAttack(Response response) {
        if (response.type == ResponseType::ATTACK) {
            if (gameModel->getTurn() == OPPONENT) {
                AttackResult attackResult = gameModel->processOpponentAttack(response.body);
                onlineGameController->postAttackResult(attackResult);
                if (gameModel->getTurn() == LOCAL_PLAYER) {
                    onlineGameController->getReadyForAnswering();
                } else if (gameModel->getTurn() == END) {
                    gameModel->setMessage("GAME END");
                } else {
                    getOpponentMove();
                }
            }
        } else {
            processResponse(response);
        }
    }

    /**
    * @brief Process responses from the opponent.
    *
    * Handles responses from the opponent when it's not an attack move.
    *
    * @param response The response from the opponent.
    */
    void processResponse(Response response) {
        if (gameModel->getTurn() == OPPONENT) {
            onlineGameController->postError();
            getOpponentMove();
        }
    }

    /**
     * @brief Handle an incorrect move input.
     *
     * Clears the text input and displays an error message.
     */
    void wrongMove() {
        gameModel->clearText();//.clear();
        gameModel->setMessage("WRONG MOVE!");
    }

private:
    GameModel* gameModel; ///< Pointer to the associated `GameModel` object.
    OnlineGameController* onlineGameController; ///< Pointer to the online game controller.
};


#endif //UNTITLED_GAMECONTROLLER_H
/* After moving definition to new file
 * In file included from C:/bernie/pw/SEM VI/openGL-ships/App/WebServices/ConnectionManager.h:16,
                 from C:/bernie/pw/SEM VI/openGL-ships/App/WebServices/OnlineGameController.h:9,
                 from C:\bernie\pw\SEM VI\openGL-ships\App\Game\GameController.h:9,
                 from C:\bernie\pw\SEM VI\openGL-ships\App\Game\GameController.cpp:2:
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:148:41: error: expected class-name before '{' token
  148 |   struct IStringList : public IDispatch {
      |                                         ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:150:37: error: 'VARIANT' has not been declared
  150 |     virtual HRESULT WINAPI get_Item(VARIANT i,VARIANT *pVariantReturn) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:150:47: error: 'VARIANT' has not been declared
  150 |     virtual HRESULT WINAPI get_Item(VARIANT i,VARIANT *pVariantReturn) = 0;
      |                                               ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:152:41: error: 'IUnknown' has not been declared
  152 |     virtual HRESULT WINAPI get__NewEnum(IUnknown **ppEnumReturn) = 0;
      |                                         ^~~~~~~~
In file included from C:/bernie/pw/SEM VI/openGL-ships/App/WebServices/ConnectionManager.h:16,
                 from C:/bernie/pw/SEM VI/openGL-ships/App/WebServices/OnlineGameController.h:9,
                 from C:\bernie\pw\SEM VI\openGL-ships\App\Game\GameController.h:9,
                 from C:\bernie\pw\SEM VI\openGL-ships\App\Game\GameController.cpp:2:
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:185:63: error: 'VARIANT' has not been declared
  185 |   HRESULT WINAPI IStringList_get_Item_Proxy(IStringList *This,VARIANT i,VARIANT *pVariantReturn);
      |                                                               ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:185:73: error: 'VARIANT' has not been declared
  185 |   HRESULT WINAPI IStringList_get_Item_Proxy(IStringList *This,VARIANT i,VARIANT *pVariantReturn);
      |                                                                         ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:189:67: error: 'IUnknown' has not been declared
  189 |   HRESULT WINAPI IStringList_get__NewEnum_Proxy(IStringList *This,IUnknown **ppEnumReturn);
      |                                                                   ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:197:48: error: expected class-name before '{' token
  197 |   struct IRequestDictionary : public IDispatch {
      |                                                ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:199:37: error: 'VARIANT' has not been declared
  199 |     virtual HRESULT WINAPI get_Item(VARIANT Var,VARIANT *pVariantReturn) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:199:49: error: 'VARIANT' has not been declared
  199 |     virtual HRESULT WINAPI get_Item(VARIANT Var,VARIANT *pVariantReturn) = 0;
      |                                                 ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:200:41: error: 'IUnknown' has not been declared
  200 |     virtual HRESULT WINAPI get__NewEnum(IUnknown **ppEnumReturn) = 0;
      |                                         ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:202:36: error: 'VARIANT' has not been declared
  202 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:202:51: error: 'VARIANT' has not been declared
  202 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                                   ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:237:77: error: 'VARIANT' has not been declared
  237 |   HRESULT WINAPI IRequestDictionary_get_Item_Proxy(IRequestDictionary *This,VARIANT Var,VARIANT *pVariantReturn);
      |                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:237:89: error: 'VARIANT' has not been declared
  237 |   HRESULT WINAPI IRequestDictionary_get_Item_Proxy(IRequestDictionary *This,VARIANT Var,VARIANT *pVariantReturn);
      |                                                                                         ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:239:81: error: 'IUnknown' has not been declared
  239 |   HRESULT WINAPI IRequestDictionary_get__NewEnum_Proxy(IRequestDictionary *This,IUnknown **ppEnumReturn);
      |                                                                                 ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:243:76: error: 'VARIANT' has not been declared
  243 |   HRESULT WINAPI IRequestDictionary_get_Key_Proxy(IRequestDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                            ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:243:91: error: 'VARIANT' has not been declared
  243 |   HRESULT WINAPI IRequestDictionary_get_Key_Proxy(IRequestDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                                           ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:251:38: error: expected class-name before '{' token
  251 |   struct IRequest : public IDispatch {
      |                                      ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:253:37: error: 'BSTR' has not been declared
  253 |     virtual HRESULT WINAPI get_Item(BSTR bstrVar,IDispatch **ppObjReturn) = 0;
      |                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:253:50: error: 'IDispatch' has not been declared
  253 |     virtual HRESULT WINAPI get_Item(BSTR bstrVar,IDispatch **ppObjReturn) = 0;
      |                                                  ^~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:261:39: error: 'VARIANT' has not been declared
  261 |     virtual HRESULT WINAPI BinaryRead(VARIANT *pvarCountToRead,VARIANT *pvarReturn) = 0;
      |                                       ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:261:64: error: 'VARIANT' has not been declared
  261 |     virtual HRESULT WINAPI BinaryRead(VARIANT *pvarCountToRead,VARIANT *pvarReturn) = 0;
      |                                                                ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:306:57: error: 'BSTR' has not been declared
  306 |   HRESULT WINAPI IRequest_get_Item_Proxy(IRequest *This,BSTR bstrVar,IDispatch **ppObjReturn);
      |                                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:306:70: error: 'IDispatch' has not been declared
  306 |   HRESULT WINAPI IRequest_get_Item_Proxy(IRequest *This,BSTR bstrVar,IDispatch **ppObjReturn);
      |                                                                      ^~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:322:59: error: 'VARIANT' has not been declared
  322 |   HRESULT WINAPI IRequest_BinaryRead_Proxy(IRequest *This,VARIANT *pvarCountToRead,VARIANT *pvarReturn);
      |                                                           ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:322:84: error: 'VARIANT' has not been declared
  322 |   HRESULT WINAPI IRequest_BinaryRead_Proxy(IRequest *This,VARIANT *pvarCountToRead,VARIANT *pvarReturn);
      |                                                                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:335:41: error: expected class-name before '{' token
  335 |   struct IReadCookie : public IDispatch {
      |                                         ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:337:37: error: 'VARIANT' has not been declared
  337 |     virtual HRESULT WINAPI get_Item(VARIANT Var,VARIANT *pVariantReturn) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:337:49: error: 'VARIANT' has not been declared
  337 |     virtual HRESULT WINAPI get_Item(VARIANT Var,VARIANT *pVariantReturn) = 0;
      |                                                 ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:338:40: error: 'VARIANT_BOOL' has not been declared
  338 |     virtual HRESULT WINAPI get_HasKeys(VARIANT_BOOL *pfHasKeys) = 0;
      |                                        ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:339:41: error: 'IUnknown' has not been declared
  339 |     virtual HRESULT WINAPI get__NewEnum(IUnknown **ppEnumReturn) = 0;
      |                                         ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:341:36: error: 'VARIANT' has not been declared
  341 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:341:51: error: 'VARIANT' has not been declared
  341 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                                   ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:378:63: error: 'VARIANT' has not been declared
  378 |   HRESULT WINAPI IReadCookie_get_Item_Proxy(IReadCookie *This,VARIANT Var,VARIANT *pVariantReturn);
      |                                                               ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:378:75: error: 'VARIANT' has not been declared
  378 |   HRESULT WINAPI IReadCookie_get_Item_Proxy(IReadCookie *This,VARIANT Var,VARIANT *pVariantReturn);
      |                                                                           ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:380:66: error: 'VARIANT_BOOL' has not been declared
  380 |   HRESULT WINAPI IReadCookie_get_HasKeys_Proxy(IReadCookie *This,VARIANT_BOOL *pfHasKeys);
      |                                                                  ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:382:67: error: 'IUnknown' has not been declared
  382 |   HRESULT WINAPI IReadCookie_get__NewEnum_Proxy(IReadCookie *This,IUnknown **ppEnumReturn);
      |                                                                   ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:386:62: error: 'VARIANT' has not been declared
  386 |   HRESULT WINAPI IReadCookie_get_Key_Proxy(IReadCookie *This,VARIANT VarKey,VARIANT *pvar);
      |                                                              ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:386:77: error: 'VARIANT' has not been declared
  386 |   HRESULT WINAPI IReadCookie_get_Key_Proxy(IReadCookie *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:394:42: error: expected class-name before '{' token
  394 |   struct IWriteCookie : public IDispatch {
      |                                          ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:396:37: error: 'VARIANT' has not been declared
  396 |     virtual HRESULT WINAPI put_Item(VARIANT key,BSTR bstrValue) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:396:49: error: 'BSTR' has not been declared
  396 |     virtual HRESULT WINAPI put_Item(VARIANT key,BSTR bstrValue) = 0;
      |                                                 ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:397:40: error: 'DATE' has not been declared
  397 |     virtual HRESULT WINAPI put_Expires(DATE dtExpires) = 0;
      |                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:398:39: error: 'BSTR' has not been declared
  398 |     virtual HRESULT WINAPI put_Domain(BSTR bstrDomain) = 0;
      |                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:399:37: error: 'BSTR' has not been declared
  399 |     virtual HRESULT WINAPI put_Path(BSTR bstrPath) = 0;
      |                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:400:39: error: 'VARIANT_BOOL' has not been declared
  400 |     virtual HRESULT WINAPI put_Secure(VARIANT_BOOL fSecure) = 0;
      |                                       ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:401:40: error: 'VARIANT_BOOL' has not been declared
  401 |     virtual HRESULT WINAPI get_HasKeys(VARIANT_BOOL *pfHasKeys) = 0;
      |                                        ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:402:41: error: 'IUnknown' has not been declared
  402 |     virtual HRESULT WINAPI get__NewEnum(IUnknown **ppEnumReturn) = 0;
      |                                         ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:443:65: error: 'VARIANT' has not been declared
  443 |   HRESULT WINAPI IWriteCookie_put_Item_Proxy(IWriteCookie *This,VARIANT key,BSTR bstrValue);
      |                                                                 ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:443:77: error: 'BSTR' has not been declared
  443 |   HRESULT WINAPI IWriteCookie_put_Item_Proxy(IWriteCookie *This,VARIANT key,BSTR bstrValue);
      |                                                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:445:68: error: 'DATE' has not been declared
  445 |   HRESULT WINAPI IWriteCookie_put_Expires_Proxy(IWriteCookie *This,DATE dtExpires);
      |                                                                    ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:447:67: error: 'BSTR' has not been declared
  447 |   HRESULT WINAPI IWriteCookie_put_Domain_Proxy(IWriteCookie *This,BSTR bstrDomain);
      |                                                                   ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:449:65: error: 'BSTR' has not been declared
  449 |   HRESULT WINAPI IWriteCookie_put_Path_Proxy(IWriteCookie *This,BSTR bstrPath);
      |                                                                 ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:451:67: error: 'VARIANT_BOOL' has not been declared
  451 |   HRESULT WINAPI IWriteCookie_put_Secure_Proxy(IWriteCookie *This,VARIANT_BOOL fSecure);
      |                                                                   ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:453:68: error: 'VARIANT_BOOL' has not been declared
  453 |   HRESULT WINAPI IWriteCookie_get_HasKeys_Proxy(IWriteCookie *This,VARIANT_BOOL *pfHasKeys);
      |                                                                    ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:455:69: error: 'IUnknown' has not been declared
  455 |   HRESULT WINAPI IWriteCookie_get__NewEnum_Proxy(IWriteCookie *This,IUnknown **ppEnumReturn);
      |                                                                     ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:463:39: error: expected class-name before '{' token
  463 |   struct IResponse : public IDispatch {
      |                                       ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:465:39: error: 'VARIANT_BOOL' has not been declared
  465 |     virtual HRESULT WINAPI get_Buffer(VARIANT_BOOL *fIsBuffering) = 0;
      |                                       ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:466:39: error: 'VARIANT_BOOL' has not been declared
  466 |     virtual HRESULT WINAPI put_Buffer(VARIANT_BOOL fIsBuffering) = 0;
      |                                       ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:467:44: error: 'BSTR' has not been declared
  467 |     virtual HRESULT WINAPI get_ContentType(BSTR *pbstrContentTypeRet) = 0;
      |                                            ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:468:44: error: 'BSTR' has not been declared
  468 |     virtual HRESULT WINAPI put_ContentType(BSTR bstrContentType) = 0;
      |                                            ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:469:40: error: 'VARIANT' has not been declared
  469 |     virtual HRESULT WINAPI get_Expires(VARIANT *pvarExpiresMinutesRet) = 0;
      |                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:471:48: error: 'VARIANT' has not been declared
  471 |     virtual HRESULT WINAPI get_ExpiresAbsolute(VARIANT *pvarExpiresRet) = 0;
      |                                                ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:472:48: error: 'DATE' has not been declared
  472 |     virtual HRESULT WINAPI put_ExpiresAbsolute(DATE dtExpires) = 0;
      |                                                ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:474:39: error: 'BSTR' has not been declared
  474 |     virtual HRESULT WINAPI get_Status(BSTR *pbstrStatusRet) = 0;
      |                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:475:39: error: 'BSTR' has not been declared
  475 |     virtual HRESULT WINAPI put_Status(BSTR bstrStatus) = 0;
      |                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:476:32: error: 'BSTR' has not been declared
  476 |     virtual HRESULT WINAPI Add(BSTR bstrHeaderValue,BSTR bstrHeaderName) = 0;
      |                                ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:476:53: error: 'BSTR' has not been declared
  476 |     virtual HRESULT WINAPI Add(BSTR bstrHeaderValue,BSTR bstrHeaderName) = 0;
      |                                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:477:38: error: 'BSTR' has not been declared
  477 |     virtual HRESULT WINAPI AddHeader(BSTR bstrHeaderName,BSTR bstrHeaderValue) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:477:58: error: 'BSTR' has not been declared
  477 |     virtual HRESULT WINAPI AddHeader(BSTR bstrHeaderName,BSTR bstrHeaderValue) = 0;
      |                                                          ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:478:40: error: 'BSTR' has not been declared
  478 |     virtual HRESULT WINAPI AppendToLog(BSTR bstrLogEntry) = 0;
      |                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:479:40: error: 'VARIANT' has not been declared
  479 |     virtual HRESULT WINAPI BinaryWrite(VARIANT varInput) = 0;
      |                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:483:37: error: 'BSTR' has not been declared
  483 |     virtual HRESULT WINAPI Redirect(BSTR bstrURL) = 0;
      |                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:484:34: error: 'VARIANT' has not been declared
  484 |     virtual HRESULT WINAPI Write(VARIANT varText) = 0;
      |                                  ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:486:46: error: 'VARIANT_BOOL' has not been declared
  486 |     virtual HRESULT WINAPI IsClientConnected(VARIANT_BOOL *pfIsClientConnected) = 0;
      |                                              ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:487:40: error: 'BSTR' has not been declared
  487 |     virtual HRESULT WINAPI get_CharSet(BSTR *pbstrCharSetRet) = 0;
      |                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:488:40: error: 'BSTR' has not been declared
  488 |     virtual HRESULT WINAPI put_CharSet(BSTR bstrCharSet) = 0;
      |                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:489:33: error: 'BSTR' has not been declared
  489 |     virtual HRESULT WINAPI Pics(BSTR bstrHeaderValue) = 0;
      |                                 ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:490:45: error: 'BSTR' has not been declared
  490 |     virtual HRESULT WINAPI get_CacheControl(BSTR *pbstrCacheControl) = 0;
      |                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:491:45: error: 'BSTR' has not been declared
  491 |     virtual HRESULT WINAPI put_CacheControl(BSTR bstrCacheControl) = 0;
      |                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:572:61: error: 'VARIANT_BOOL' has not been declared
  572 |   HRESULT WINAPI IResponse_get_Buffer_Proxy(IResponse *This,VARIANT_BOOL *fIsBuffering);
      |                                                             ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:574:61: error: 'VARIANT_BOOL' has not been declared
  574 |   HRESULT WINAPI IResponse_put_Buffer_Proxy(IResponse *This,VARIANT_BOOL fIsBuffering);
      |                                                             ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:576:66: error: 'BSTR' has not been declared
  576 |   HRESULT WINAPI IResponse_get_ContentType_Proxy(IResponse *This,BSTR *pbstrContentTypeRet);
      |                                                                  ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:578:66: error: 'BSTR' has not been declared
  578 |   HRESULT WINAPI IResponse_put_ContentType_Proxy(IResponse *This,BSTR bstrContentType);
      |                                                                  ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:580:62: error: 'VARIANT' has not been declared
  580 |   HRESULT WINAPI IResponse_get_Expires_Proxy(IResponse *This,VARIANT *pvarExpiresMinutesRet);
      |                                                              ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:584:70: error: 'VARIANT' has not been declared
  584 |   HRESULT WINAPI IResponse_get_ExpiresAbsolute_Proxy(IResponse *This,VARIANT *pvarExpiresRet);
      |                                                                      ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:586:70: error: 'DATE' has not been declared
  586 |   HRESULT WINAPI IResponse_put_ExpiresAbsolute_Proxy(IResponse *This,DATE dtExpires);
      |                                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:590:61: error: 'BSTR' has not been declared
  590 |   HRESULT WINAPI IResponse_get_Status_Proxy(IResponse *This,BSTR *pbstrStatusRet);
      |                                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:592:61: error: 'BSTR' has not been declared
  592 |   HRESULT WINAPI IResponse_put_Status_Proxy(IResponse *This,BSTR bstrStatus);
      |                                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:594:54: error: 'BSTR' has not been declared
  594 |   HRESULT WINAPI IResponse_Add_Proxy(IResponse *This,BSTR bstrHeaderValue,BSTR bstrHeaderName);
      |                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:594:75: error: 'BSTR' has not been declared
  594 |   HRESULT WINAPI IResponse_Add_Proxy(IResponse *This,BSTR bstrHeaderValue,BSTR bstrHeaderName);
      |                                                                           ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:596:60: error: 'BSTR' has not been declared
  596 |   HRESULT WINAPI IResponse_AddHeader_Proxy(IResponse *This,BSTR bstrHeaderName,BSTR bstrHeaderValue);
      |                                                            ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:596:80: error: 'BSTR' has not been declared
  596 |   HRESULT WINAPI IResponse_AddHeader_Proxy(IResponse *This,BSTR bstrHeaderName,BSTR bstrHeaderValue);
      |                                                                                ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:598:62: error: 'BSTR' has not been declared
  598 |   HRESULT WINAPI IResponse_AppendToLog_Proxy(IResponse *This,BSTR bstrLogEntry);
      |                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:600:62: error: 'VARIANT' has not been declared
  600 |   HRESULT WINAPI IResponse_BinaryWrite_Proxy(IResponse *This,VARIANT varInput);
      |                                                              ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:608:59: error: 'BSTR' has not been declared
  608 |   HRESULT WINAPI IResponse_Redirect_Proxy(IResponse *This,BSTR bstrURL);
      |                                                           ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:610:56: error: 'VARIANT' has not been declared
  610 |   HRESULT WINAPI IResponse_Write_Proxy(IResponse *This,VARIANT varText);
      |                                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:614:68: error: 'VARIANT_BOOL' has not been declared
  614 |   HRESULT WINAPI IResponse_IsClientConnected_Proxy(IResponse *This,VARIANT_BOOL *pfIsClientConnected);
      |                                                                    ^~~~~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:616:62: error: 'BSTR' has not been declared
  616 |   HRESULT WINAPI IResponse_get_CharSet_Proxy(IResponse *This,BSTR *pbstrCharSetRet);
      |                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:618:62: error: 'BSTR' has not been declared
  618 |   HRESULT WINAPI IResponse_put_CharSet_Proxy(IResponse *This,BSTR bstrCharSet);
      |                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:620:55: error: 'BSTR' has not been declared
  620 |   HRESULT WINAPI IResponse_Pics_Proxy(IResponse *This,BSTR bstrHeaderValue);
      |                                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:622:67: error: 'BSTR' has not been declared
  622 |   HRESULT WINAPI IResponse_get_CacheControl_Proxy(IResponse *This,BSTR *pbstrCacheControl);
      |                                                                   ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:624:67: error: 'BSTR' has not been declared
  624 |   HRESULT WINAPI IResponse_put_CacheControl_Proxy(IResponse *This,BSTR bstrCacheControl);
      |                                                                   ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:637:48: error: expected class-name before '{' token
  637 |   struct IVariantDictionary : public IDispatch {
      |                                                ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:639:37: error: 'VARIANT' has not been declared
  639 |     virtual HRESULT WINAPI get_Item(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:639:52: error: 'VARIANT' has not been declared
  639 |     virtual HRESULT WINAPI get_Item(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:640:37: error: 'VARIANT' has not been declared
  640 |     virtual HRESULT WINAPI put_Item(VARIANT VarKey,VARIANT var) = 0;
      |                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:640:52: error: 'VARIANT' has not been declared
  640 |     virtual HRESULT WINAPI put_Item(VARIANT VarKey,VARIANT var) = 0;
      |                                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:641:40: error: 'VARIANT' has not been declared
  641 |     virtual HRESULT WINAPI putref_Item(VARIANT VarKey,VARIANT var) = 0;
      |                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:641:55: error: 'VARIANT' has not been declared
  641 |     virtual HRESULT WINAPI putref_Item(VARIANT VarKey,VARIANT var) = 0;
      |                                                       ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:642:36: error: 'VARIANT' has not been declared
  642 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                    ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:642:51: error: 'VARIANT' has not been declared
  642 |     virtual HRESULT WINAPI get_Key(VARIANT VarKey,VARIANT *pvar) = 0;
      |                                                   ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:644:41: error: 'IUnknown' has not been declared
  644 |     virtual HRESULT WINAPI get__NewEnum(IUnknown **ppEnumReturn) = 0;
      |                                         ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:645:35: error: 'VARIANT' has not been declared
  645 |     virtual HRESULT WINAPI Remove(VARIANT VarKey) = 0;
      |                                   ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:689:77: error: 'VARIANT' has not been declared
  689 |   HRESULT WINAPI IVariantDictionary_get_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:689:92: error: 'VARIANT' has not been declared
  689 |   HRESULT WINAPI IVariantDictionary_get_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                                            ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:691:77: error: 'VARIANT' has not been declared
  691 |   HRESULT WINAPI IVariantDictionary_put_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT var);
      |                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:691:92: error: 'VARIANT' has not been declared
  691 |   HRESULT WINAPI IVariantDictionary_put_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT var);
      |                                                                                            ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:693:80: error: 'VARIANT' has not been declared
  693 |   HRESULT WINAPI IVariantDictionary_putref_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT var);
      |                                                                                ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:693:95: error: 'VARIANT' has not been declared
  693 |   HRESULT WINAPI IVariantDictionary_putref_Item_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT var);
      |                                                                                               ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:695:76: error: 'VARIANT' has not been declared
  695 |   HRESULT WINAPI IVariantDictionary_get_Key_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                            ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:695:91: error: 'VARIANT' has not been declared
  695 |   HRESULT WINAPI IVariantDictionary_get_Key_Proxy(IVariantDictionary *This,VARIANT VarKey,VARIANT *pvar);
      |                                                                                           ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:699:81: error: 'IUnknown' has not been declared
  699 |   HRESULT WINAPI IVariantDictionary_get__NewEnum_Proxy(IVariantDictionary *This,IUnknown **ppEnumReturn);
      |                                                                                 ^~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:701:75: error: 'VARIANT' has not been declared
  701 |   HRESULT WINAPI IVariantDictionary_Remove_Proxy(IVariantDictionary *This,VARIANT VarKey);
      |                                                                           ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:711:44: error: expected class-name before '{' token
  711 |   struct ISessionObject : public IDispatch {
      |                                            ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:713:42: error: 'BSTR' has not been declared
  713 |     virtual HRESULT WINAPI get_SessionID(BSTR *pbstrRet) = 0;
      |                                          ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:714:38: error: 'BSTR' has not been declared
  714 |     virtual HRESULT WINAPI get_Value(BSTR bstrValue,VARIANT *pvar) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:714:53: error: 'VARIANT' has not been declared
  714 |     virtual HRESULT WINAPI get_Value(BSTR bstrValue,VARIANT *pvar) = 0;
      |                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:715:38: error: 'BSTR' has not been declared
  715 |     virtual HRESULT WINAPI put_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:715:53: error: 'VARIANT' has not been declared
  715 |     virtual HRESULT WINAPI put_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:716:41: error: 'BSTR' has not been declared
  716 |     virtual HRESULT WINAPI putref_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:716:56: error: 'VARIANT' has not been declared
  716 |     virtual HRESULT WINAPI putref_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:778:74: error: 'BSTR' has not been declared
  778 |   HRESULT WINAPI ISessionObject_get_SessionID_Proxy(ISessionObject *This,BSTR *pbstrRet);
      |                                                                          ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:780:70: error: 'BSTR' has not been declared
  780 |   HRESULT WINAPI ISessionObject_get_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT *pvar);
      |                                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:780:85: error: 'VARIANT' has not been declared
  780 |   HRESULT WINAPI ISessionObject_get_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT *pvar);
      |                                                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:782:70: error: 'BSTR' has not been declared
  782 |   HRESULT WINAPI ISessionObject_put_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT var);
      |                                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:782:85: error: 'VARIANT' has not been declared
  782 |   HRESULT WINAPI ISessionObject_put_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT var);
      |                                                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:784:73: error: 'BSTR' has not been declared
  784 |   HRESULT WINAPI ISessionObject_putref_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT var);
      |                                                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:784:88: error: 'VARIANT' has not been declared
  784 |   HRESULT WINAPI ISessionObject_putref_Value_Proxy(ISessionObject *This,BSTR bstrValue,VARIANT var);
      |                                                                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:815:48: error: expected class-name before '{' token
  815 |   struct IApplicationObject : public IDispatch {
      |                                                ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:817:38: error: 'BSTR' has not been declared
  817 |     virtual HRESULT WINAPI get_Value(BSTR bstrValue,VARIANT *pvar) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:817:53: error: 'VARIANT' has not been declared
  817 |     virtual HRESULT WINAPI get_Value(BSTR bstrValue,VARIANT *pvar) = 0;
      |                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:818:38: error: 'BSTR' has not been declared
  818 |     virtual HRESULT WINAPI put_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:818:53: error: 'VARIANT' has not been declared
  818 |     virtual HRESULT WINAPI put_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                                     ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:819:41: error: 'BSTR' has not been declared
  819 |     virtual HRESULT WINAPI putref_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:819:56: error: 'VARIANT' has not been declared
  819 |     virtual HRESULT WINAPI putref_Value(BSTR bstrValue,VARIANT var) = 0;
      |                                                        ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:864:78: error: 'BSTR' has not been declared
  864 |   HRESULT WINAPI IApplicationObject_get_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT *pvar);
      |                                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:864:93: error: 'VARIANT' has not been declared
  864 |   HRESULT WINAPI IApplicationObject_get_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT *pvar);
      |                                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:866:78: error: 'BSTR' has not been declared
  866 |   HRESULT WINAPI IApplicationObject_put_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT var);
      |                                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:866:93: error: 'VARIANT' has not been declared
  866 |   HRESULT WINAPI IApplicationObject_put_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT var);
      |                                                                                             ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:868:81: error: 'BSTR' has not been declared
  868 |   HRESULT WINAPI IApplicationObject_putref_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT var);
      |                                                                                 ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:868:96: error: 'VARIANT' has not been declared
  868 |   HRESULT WINAPI IApplicationObject_putref_Value_Proxy(IApplicationObject *This,BSTR bstrValue,VARIANT var);
      |                                                                                                ^~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:889:39: error: expected class-name before '{' token
  889 |   struct IASPError : public IDispatch {
      |                                       ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:891:40: error: 'BSTR' has not been declared
  891 |     virtual HRESULT WINAPI get_ASPCode(BSTR *pbstrASPCode) = 0;
      |                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:893:41: error: 'BSTR' has not been declared
  893 |     virtual HRESULT WINAPI get_Category(BSTR *pbstrSource) = 0;
      |                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:894:37: error: 'BSTR' has not been declared
  894 |     virtual HRESULT WINAPI get_File(BSTR *pbstrFileName) = 0;
      |                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:896:44: error: 'BSTR' has not been declared
  896 |     virtual HRESULT WINAPI get_Description(BSTR *pbstrDescription) = 0;
      |                                            ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:897:47: error: 'BSTR' has not been declared
  897 |     virtual HRESULT WINAPI get_ASPDescription(BSTR *pbstrDescription) = 0;
      |                                               ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:899:39: error: 'BSTR' has not been declared
  899 |     virtual HRESULT WINAPI get_Source(BSTR *pbstrLineText) = 0;
      |                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:944:62: error: 'BSTR' has not been declared
  944 |   HRESULT WINAPI IASPError_get_ASPCode_Proxy(IASPError *This,BSTR *pbstrASPCode);
      |                                                              ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:948:63: error: 'BSTR' has not been declared
  948 |   HRESULT WINAPI IASPError_get_Category_Proxy(IASPError *This,BSTR *pbstrSource);
      |                                                               ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:950:59: error: 'BSTR' has not been declared
  950 |   HRESULT WINAPI IASPError_get_File_Proxy(IASPError *This,BSTR *pbstrFileName);
      |                                                           ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:954:66: error: 'BSTR' has not been declared
  954 |   HRESULT WINAPI IASPError_get_Description_Proxy(IASPError *This,BSTR *pbstrDescription);
      |                                                                  ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:956:69: error: 'BSTR' has not been declared
  956 |   HRESULT WINAPI IASPError_get_ASPDescription_Proxy(IASPError *This,BSTR *pbstrDescription);
      |                                                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:960:61: error: 'BSTR' has not been declared
  960 |   HRESULT WINAPI IASPError_get_Source_Proxy(IASPError *This,BSTR *pbstrLineText);
      |                                                             ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:968:37: error: expected class-name before '{' token
  968 |   struct IServer : public IDispatch {
      |                                     ^
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:972:41: error: 'BSTR' has not been declared
  972 |     virtual HRESULT WINAPI CreateObject(BSTR bstrProgID,IDispatch **ppDispObject) = 0;
      |                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:972:57: error: 'IDispatch' has not been declared
  972 |     virtual HRESULT WINAPI CreateObject(BSTR bstrProgID,IDispatch **ppDispObject) = 0;
      |                                                         ^~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:973:39: error: 'BSTR' has not been declared
  973 |     virtual HRESULT WINAPI HTMLEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:973:51: error: 'BSTR' has not been declared
  973 |     virtual HRESULT WINAPI HTMLEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                                   ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:974:36: error: 'BSTR' has not been declared
  974 |     virtual HRESULT WINAPI MapPath(BSTR bstrLogicalPath,BSTR *pbstrPhysicalPath) = 0;
      |                                    ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:974:57: error: 'BSTR' has not been declared
  974 |     virtual HRESULT WINAPI MapPath(BSTR bstrLogicalPath,BSTR *pbstrPhysicalPath) = 0;
      |                                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:975:38: error: 'BSTR' has not been declared
  975 |     virtual HRESULT WINAPI URLEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:975:50: error: 'BSTR' has not been declared
  975 |     virtual HRESULT WINAPI URLEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                                  ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:976:42: error: 'BSTR' has not been declared
  976 |     virtual HRESULT WINAPI URLPathEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                          ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:976:54: error: 'BSTR' has not been declared
  976 |     virtual HRESULT WINAPI URLPathEncode(BSTR bstrIn,BSTR *pbstrEncoded) = 0;
      |                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:977:36: error: 'BSTR' has not been declared
  977 |     virtual HRESULT WINAPI Execute(BSTR bstrLogicalPath) = 0;
      |                                    ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:978:37: error: 'BSTR' has not been declared
  978 |     virtual HRESULT WINAPI Transfer(BSTR bstrLogicalPath) = 0;
      |                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1030:59: error: 'BSTR' has not been declared
 1030 |   HRESULT WINAPI IServer_CreateObject_Proxy(IServer *This,BSTR bstrProgID,IDispatch **ppDispObject);
      |                                                           ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1030:75: error: 'IDispatch' has not been declared
 1030 |   HRESULT WINAPI IServer_CreateObject_Proxy(IServer *This,BSTR bstrProgID,IDispatch **ppDispObject);
      |                                                                           ^~~~~~~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1032:57: error: 'BSTR' has not been declared
 1032 |   HRESULT WINAPI IServer_HTMLEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                         ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1032:69: error: 'BSTR' has not been declared
 1032 |   HRESULT WINAPI IServer_HTMLEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                                     ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1034:54: error: 'BSTR' has not been declared
 1034 |   HRESULT WINAPI IServer_MapPath_Proxy(IServer *This,BSTR bstrLogicalPath,BSTR *pbstrPhysicalPath);
      |                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1034:75: error: 'BSTR' has not been declared
 1034 |   HRESULT WINAPI IServer_MapPath_Proxy(IServer *This,BSTR bstrLogicalPath,BSTR *pbstrPhysicalPath);
      |                                                                           ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1036:56: error: 'BSTR' has not been declared
 1036 |   HRESULT WINAPI IServer_URLEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1036:68: error: 'BSTR' has not been declared
 1036 |   HRESULT WINAPI IServer_URLEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                                    ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1038:60: error: 'BSTR' has not been declared
 1038 |   HRESULT WINAPI IServer_URLPathEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                            ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1038:72: error: 'BSTR' has not been declared
 1038 |   HRESULT WINAPI IServer_URLPathEncode_Proxy(IServer *This,BSTR bstrIn,BSTR *pbstrEncoded);
      |                                                                        ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1040:54: error: 'BSTR' has not been declared
 1040 |   HRESULT WINAPI IServer_Execute_Proxy(IServer *This,BSTR bstrLogicalPath);
      |                                                      ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1042:55: error: 'BSTR' has not been declared
 1042 |   HRESULT WINAPI IServer_Transfer_Proxy(IServer *This,BSTR bstrLogicalPath);
      |                                                       ^~~~
C:/Users/joyjo/Downloads/mingw/mingw/x86_64-w64-mingw32/include/asptlb.h:1057:47: error: expected class-name before '{' token
 1057 |   struct IScriptingContext : public IDispatch {
      |                                               ^
mingw32-make[3]: *** [CMakeFiles\untitled.dir\build.make:391: CMakeFiles/untitled.dir/App/Game/GameController.cpp.obj] Error 1
mingw32-make[3]: *** Waiting for unfinished jobs....
mingw32-make[2]: *** [CMakeFiles\Makefile2:82: CMakeFiles/untitled.dir/all] Error 2
mingw32-make[1]: *** [CMakeFiles\Makefile2:89: CMakeFiles/untitled.dir/rule] Error 2
mingw32-make: *** [Makefile:123: untitled] Error 2
 */