import aiohttp
import asyncio
from PyPDF2 import PdfReader
from io import BytesIO

async def fetch_pdf(session, url, n):
    try:
        async with session.get(url) as response:
            if response.status == 200 and response.headers.get('Content-Type') == 'application/pdf':
                # Read PDF content synchronously
                pdf = PdfReader(BytesIO(await response.read()))
                first_page_text = pdf.pages[0].extract_text()

                # Check if "reloaded" (case-insensitive) is in the title or content of the first page
                if "reloaded" in first_page_text.lower():
                    print(f"Found 'reloaded' in PDF at n={n}: {url}")
                    return url  # Return the URL of the largest matching PDF
    except Exception as e:
        print(f"Error reading PDF at n={n}: {e}")
    return None

async def find_largest_reloaded_pdf():
    base_url = "https://cdn.intra.42.fr/pdf/pdf/{}/en.subject.pdf"
    tasks = []

    async with aiohttp.ClientSession() as session:
        # Create a task for each `n` value from 200000 down to 0
        for n in range(150000, -1, -1):
            if n%500==0:
                print(f"{n: <8}",100-100*n/200000)
            url = base_url.format(n)
            task = fetch_pdf(session, url, n)
            tasks.append(task)

            # Limit the number of concurrent requests
            if len(tasks) >= 100:  # Adjust concurrency limit as needed
                results = await asyncio.gather(*tasks)
                tasks = []  # Reset tasks list after each batch

                # Check for any successful result in the batch
                for result in results:
                    if result:
                        pass
                        #return result  # Return as soon as the largest matching PDF is found

        # Final batch of tasks (for any remaining numbers)
        if tasks:
            results = await asyncio.gather(*tasks)
            for result in results:
                if result:
                    return result

    print("No PDF with 'reloaded' found within the specified range.")
    return None

# Run the function
largest_reloaded_pdf_url = asyncio.run(find_largest_reloaded_pdf())
if largest_reloaded_pdf_url:
    print("Largest 'reloaded' PDF URL:", largest_reloaded_pdf_url)
else:
    print("No 'reloaded' PDF found.")

