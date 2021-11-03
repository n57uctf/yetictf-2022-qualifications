import random  
import string

from pikepdf import Pdf
from werkzeug.utils import secure_filename


class PDFReverser(object):
    """
    1. Page Count+
    2. Metadata+
    3. Pdf version
    4. Pdf reverse+
    """
    def __init__(self, path) -> None:
        self.pdf = Pdf.open(path)

    def version(self):
        return self.pdf.pdf_version

    def page_count(self):
        return len(self.pdf.pages)

    def meta_data(self):
        with self.pdf.open_metadata(set_pikepdf_as_editor=False, update_docinfo=False, strict=True) as m:
            if str(m) == '<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="pikepdf">\n <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">\n </rdf:RDF>\n</x:xmpmeta>\n':
                return "No metadata"
            else:
                return(str(m))

    def reverse(self):
        self.pdf.pages.reverse()
        filename = self.__random_file_name() + ".pdf"
        self.pdf.save(f"/tmp/pdfcache/{filename}")
        return filename


    def __random_file_name(self, letter_count=16, digit_count=16):  
        str1 = ''.join((random.choice(string.ascii_letters) for x in range(letter_count)))  
        str1 += ''.join((random.choice(string.digits) for x in range(digit_count)))  
        sam_list = list(str1) # it converts the string to list.  
        random.shuffle(sam_list) # It uses a random.shuffle() function to shuffle the string.  
        final_string = ''.join(sam_list)  
        return final_string 