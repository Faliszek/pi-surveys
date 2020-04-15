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
      <Text className=[FontSize(Text2xl), Margin(Mr4)]>
        {j|Lista ankiet|j}
      </Text>
      <Button onClick={_ => ReasonReactRouter.push("/create-survey")}>
        <Text color=`white> {j|Utwórz ankietę|j} </Text>
      </Button>
    </div>
    {switch (surveys.response) {
     | Data(data) =>
       Js.log(data);
       let forms = data##forms##forms;

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
             <th className={th()}> <Text> {j|ID|j} </Text> </th>
             <th className={th()}> <Text> {j|Tytuł|j} </Text> </th>
             <th className={th()}> <Text> {j|Krótki opis|j} </Text> </th>
             <th className={th()}> <Text> {j|Utworzona|j} </Text> </th>
             <th className={th()}>
               <Text> {j|Ostatnia modyfikacja|j} </Text>
             </th>
             <th className={th()}> <Text> {j|Autor|j} </Text> </th>
           </thead>
           <tbody>
             {forms
              ->Belt.Array.map(s =>
                  <tr
                    className={[Cursor(CursorPointer)]->make}
                    onClick={_ => {
                      let id = s##_id;
                      ReasonReactRouter.push({j|/surveys/$id|j});
                    }}>
                    <td className={td(W1_6)}> <Text> {s##_id} </Text> </td>
                    <td className={td(W1_6)}> <Text> {s##title} </Text> </td>
                    <td className={td(W1_6)}>
                      <Text> {s##content} </Text>
                    </td>
                    <td className={td(W3_12)}>
                      <Text> {s##createdAt->formatDate} </Text>
                    </td>
                    <td className={td(W3_12)}>
                      <Text> {s##updatedAt->formatDate} </Text>
                    </td>
                    <td className={td(W2_12)}>
                      <Text> {s##creator##name} </Text>
                    </td>
                  </tr>
                )
              ->React.array}
           </tbody>
         </table>
         <div className={[Display(Flex), JustifyContent(JustifyEnd)]->make}>
           {Array.range(1, total / forms->Array.length)
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