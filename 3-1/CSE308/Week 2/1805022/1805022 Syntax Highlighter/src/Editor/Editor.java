package Editor;

import Font.Font;
import Font.FontFactory;
import Language.Language;
import Language.LanguageFactory;

public class Editor {
    private static Editor instance = null;
    private Language language;
    private Font font;
    private Editor(){

    }

    public static Editor getInstance(){
        if( instance == null )
            instance = new Editor();
        return instance;
    }

    public void setLanguage(String file_type){
        language = LanguageFactory.getLanguage(file_type);
        System.out.println(language);
        setFont(file_type);
    }
    public void setFont(String file_type){
        font = FontFactory.getFont(file_type);
        System.out.println(font);
    }
}
