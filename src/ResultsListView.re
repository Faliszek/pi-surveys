open TW;
open Belt;

let formatDate = s => {
  let date = s->Js.Date.fromString->Js.Date.toLocaleDateString;
  let time = s->Js.Date.fromString->Js.Date.toLocaleTimeString;

  date ++ ", " ++ time;
};

let th = () =>
  [
    TextAlign(TextLeft),
    Padding(P2),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray400),
  ]
  ->make;

let td = w =>
  [
    TextAlign(TextLeft),
    Padding(Py6),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray200),
    Width(w),
  ]
  ->make;

[@react.component]
let make = () => {
  let (page, setPage) = React.useState(_ => 1);
  let (surveys, _) = SurveyListQuery.use(~page);

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Wyniki|j}
      </Text>
    </div>
    {switch (surveys.response) {
     | Data(data) =>
       //mocks
       let forms =
         data##forms##forms
         ->Array.mapWithIndex((index, f) =>
             {
               "_id": f##_id,
               "title": f##title,
               "createdAt": f##createdAt,
               "creator": f##creator,
               "user": {
                 "email": "asd+" ++ index->Js.Int.toString ++ "@gmail.com",
               },
               "solved": index === 0,
             }
           );

       let formsLength = forms->Array.length === 0 ? 1 : forms->Array.length;

       let total = data##forms##totalForms;

       <div>
         <table
           className={
             [
               Width(WFull),
               Margin(My8),
               BorderRadius(RoundedLg),
               BoxShadow(Shadow),
               Padding(P8),
             ]
             ->make
           }>
           <thead>
             <tr>
               <th className={th()}> <Text> {j|ID|j} </Text> </th>
               <th className={th()}> <Text> {j|Uczestnik|j} </Text> </th>
               <th className={th()}> <Text> {j|Tytuł|j} </Text> </th>
               <th className={th()}> <Text> {j|Utworzona|j} </Text> </th>
               <th className={th()}> <Text> {j|Autor|j} </Text> </th>
             </tr>
           </thead>
           <tbody>
             {forms
              ->Belt.Array.map(s =>
                  <tr
                    className={
                      (s##solved ? [BackgroundColor(BgGreen100)] : [])->make
                    }>
                    <td className={td(W1_6)}> <Text> {s##_id} </Text> </td>
                    <td className={td(W1_6)}>
                      <Text> {s##user##email} </Text>
                    </td>
                    <td className={td(W1_6)}> <Text> {s##title} </Text> </td>
                    <td className={td(W3_12)}>
                      <Text> {s##createdAt->formatDate} </Text>
                    </td>
                    <td className={td(W2_12)}>
                      <Text>
                        {s##creator
                         ->Option.map(c => c##name)
                         ->Option.getWithDefault("-")}
                      </Text>
                    </td>
                  </tr>
                )
              ->React.array}
           </tbody>
         </table>
         <div className={[Display(Flex), JustifyContent(JustifyEnd)]->make}>
           {Array.range(1, total / formsLength)
            ->Array.map(v =>
                <div
                  className={
                    [
                      Width(W12),
                      Height(H12),
                      BoxShadow(ShadowMd),
                      BorderRadius(RoundedLg),
                      Display(Flex),
                      AlignItems(ItemsCenter),
                      JustifyContent(JustifyCenter),
                      Margin(M1),
                      BackgroundColor(BgGray100),
                      Cursor(CursorPointer),
                    ]
                    ->make
                  }
                  onClick={_ => setPage(_ => v)}>
                  <Text> v->Js.Int.toString </Text>
                </div>
              )
            ->React.array}
         </div>
       </div>;
     | Fetching => <Text> {j|Wczytywanie|j} </Text>
     | NotFound => React.null
     | Error(_) => <Text> {j|Wystąpił nieoczekiwany błąd|j} </Text>
     }}
  </Layout>;
};