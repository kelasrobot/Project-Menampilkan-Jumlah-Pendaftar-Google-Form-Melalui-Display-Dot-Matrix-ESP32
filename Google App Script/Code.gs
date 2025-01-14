function doGet(e) {
  // Dapatkan spreadsheet aktif
  var spreadsheet = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = spreadsheet.getActiveSheet();
  
  // Tentukan rentang data
  var range = sheet.getDataRange();
  var data = range.getValues();
  
  // Hitung jumlah data (mengabaikan header)
  var jumlahData = data.length - 1; // Kurangi 1 jika ada header di baris pertama
  
  // Kembalikan jumlah data dalam format JSON
  var output = {
    status: "success",
    jumlahData: jumlahData
  };
  
  return ContentService.createTextOutput(JSON.stringify(output))
                       .setMimeType(ContentService.MimeType.JSON);
}
